#include "MenuState.h"
#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"

MenuState::MenuState(const int nbButtons) : m_iNbButtons(nbButtons) {}

void MenuState::update() {
	InputHandler* handlerInstance = InputHandler::Instance();
	if (handlerInstance->joysticksInitialised()) {
		int yAxisValue = handlerInstance->stickYValue(0, LEFT_STICK);
		// The stick must be brought back to neutral position to choose another
		// menu element, otherwise, it moves too fast.
		if (m_bMenuBeingChanged && yAxisValue == 0) {
			m_bMenuBeingChanged = false;
		}
		else if (!m_bMenuBeingChanged && yAxisValue != 0) {
			// deactivate the current menu element, change the current active
			// index, activate the new current menu element
			m_vButtons[m_iActiveButtonIndex]->setActive(false);
			if (yAxisValue < 0) {
				m_iActiveButtonIndex = (m_iNbButtons + m_iActiveButtonIndex - 1) % m_iNbButtons;
			}
			else if (yAxisValue > 0) {
				m_iActiveButtonIndex = (m_iActiveButtonIndex + 1) % m_iNbButtons;
			}
			m_vButtons[m_iActiveButtonIndex]->setActive(true);
			m_bMenuBeingChanged = true;
		}

		if (InputHandler::Instance()->getButtonState(0, 0)) {
			m_vButtons[m_iActiveButtonIndex]->executeAction();
			InputHandler::Instance()->setButtonState(0, 0, false);
		}
	}
}

void MenuState::render() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_vRenderableObjects.size(); i++) {
		m_vRenderableObjects[i]->render(Game::Instance()->getRenderer());
	}
}

bool MenuState::onEnter() {
	for (int i = 0; i < m_iNbButtons; ++i) {
		m_vButtons.push_back(createButton(i));
		m_vGameObjects.push_back(m_vButtons[i]);
		m_vRenderableObjects.push_back(m_vButtons[i]);
	}
	return true;
}

bool MenuState::onExit() {
	for (int i = 0; i < m_iNbButtons; ++i) {
		delete m_vButtons[i];
		m_vButtons[i] = NULL;
		m_vGameObjects[i] = NULL;
		m_vRenderableObjects[i] = NULL;
	}
	return true;
}
