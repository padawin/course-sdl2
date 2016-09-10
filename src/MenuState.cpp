#include "MenuState.h"
#include "GameStateParser.h"
#include "ServiceProvider.h"
#include "PlayState.h"

MenuState::MenuState(const int nbButtons) : m_iNbButtons(nbButtons) {}

void MenuState::update() {
	UserActions* userActions = ServiceProvider::getUserActions();
	int setNext = userActions->getActionState("CHANGE_MENU_NEXT");
	int setPrevious = userActions->getActionState("CHANGE_MENU_PREVIOUS");
	bool menuChanged = setNext || setPrevious;
	// The stick must be brought back to neutral position to choose another
	// menu element, otherwise, it moves too fast.
	if (m_bMenuBeingChanged && !menuChanged) {
		m_bMenuBeingChanged = false;
	}
	else if (!m_bMenuBeingChanged && menuChanged) {
		// deactivate the current menu element, change the current active
		// index, activate the new current menu element
		m_vButtons[m_iActiveButtonIndex]->setActive(false);
		if (setPrevious) {
			m_iActiveButtonIndex = (m_iNbButtons + m_iActiveButtonIndex - 1) % m_iNbButtons;
		}
		// set next
		else {
			m_iActiveButtonIndex = (m_iActiveButtonIndex + 1) % m_iNbButtons;
		}
		m_vButtons[m_iActiveButtonIndex]->setActive(true);
		m_bMenuBeingChanged = true;
	}

	// If the button 0 of the joystick 0 is pressed (A on Xbox controller),
	// execute the action associated with the currently selected button
	if (userActions->getActionState("ACTIVATE_MENU_BUTTON")) {
		m_vButtons[m_iActiveButtonIndex]->executeAction();
		userActions->resetActionState("ACTIVATE_MENU_BUTTON");
	}
}

bool MenuState::onEnter() {
	// parse the state
	GameStateParser stateParser;
	bool stateParsed = stateParser.parseState(
		"configs/menus.xml",
		&m_vGameObjects,
		&m_vRenderableObjects,
		getStateID().c_str()
	);

	if (!stateParsed) {
		return false;
	}

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
	GameState::onExit();
	m_vButtons.clear();

	return true;
}
