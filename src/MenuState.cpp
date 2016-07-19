#include "MenuState.h"
#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"
#include <iostream>

MenuState::MenuState(const int nbButtons) : m_nbButtons(nbButtons) {}

void MenuState::update() {
	InputHandler* handlerInstance = InputHandler::Instance();
	if (handlerInstance->joysticksInitialised()) {
		int yAxisValue = handlerInstance->stickYValue(0, LEFT_STICK);
		// The stick must be brought back to neutral position to choose another
		// menu element, otherwise, it moves too fast.
		if (m_menuBeingChanged && yAxisValue == 0) {
			m_menuBeingChanged = false;
		}
		else if (!m_menuBeingChanged && yAxisValue != 0) {
			// deactivate the current menu element, change the current active
			// index, activate the new current menu element
			m_buttons[m_activeButtonIndex]->setActive(false);
			if (yAxisValue < 0) {
				m_activeButtonIndex = (m_nbButtons + m_activeButtonIndex - 1) % m_nbButtons;
			}
			else if (yAxisValue > 0) {
				m_activeButtonIndex = (m_activeButtonIndex + 1) % m_nbButtons;
			}
			m_buttons[m_activeButtonIndex]->setActive(true);
			m_menuBeingChanged = true;
		}

		if (InputHandler::Instance()->getButtonState(0, 0)) {
			m_buttons[m_activeButtonIndex]->executeAction();
		}
	}
}

void MenuState::render() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_renderableObjects.size(); i++) {
		m_renderableObjects[i]->render(Game::Instance()->getRenderer());
	}
}

bool MenuState::onEnter() {
	for (int i = 0; i < m_nbButtons; ++i) {
		m_buttons.push_back(createButton(i));
		m_gameObjects.push_back(m_buttons[i]);
		m_renderableObjects.push_back(m_buttons[i]);
	}
	return true;
}

bool MenuState::onExit() {
	std::cout << "exiting MenuState\n";
	return true;
}
