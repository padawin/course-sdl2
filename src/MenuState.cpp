#include "MenuState.h"
#include "Game.h"
#include "GameStateParser.h"
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

		// If the button 0 of the joystick 0 is pressed (A on Xbox controller),
		// execute the action associated with the currently selected button
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
	// parse the state
	GameStateParser stateParser;
	stateParser.parseState(
		"configs/menus.xml",
		&m_vGameObjects,
		&m_vRenderableObjects,
		getStateID().c_str()
	);
	for (std::vector<GameObject*>::size_type i = 0; i != m_vRenderableObjects.size(); i++) {
		if (dynamic_cast<MenuButton*>(m_vGameObjects[i])) {
			MenuButton* button = dynamic_cast<MenuButton*>(m_vGameObjects[i]);
			m_vButtons.push_back(button);
			button->setActive(i == 0);
			button->setAction(s_vActions[i]);
		}
	}
	return true;
}

bool MenuState::onExit() {
	for (int i = 0; i < (int) m_vButtons.size(); ++i) {
		delete m_vButtons[i];
		m_vButtons[i] = NULL;
		m_vGameObjects[i] = NULL;
		m_vRenderableObjects[i] = NULL;
	}
	return true;
}
