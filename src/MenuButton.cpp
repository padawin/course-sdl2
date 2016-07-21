#include "MenuButton.h"

void MenuButton::setActive(const bool active) {
	m_iCurrentFrame = (int) active;
}

void MenuButton::setAction(void (*callback)()) {
	m_callback = callback;
}

void MenuButton::executeAction() {
	m_callback();
}

// MENU BUTTON BASE CREATOR CLASS

GameObject* MenuButtonCreator::createGameObject() const {
	return new MenuButton();
}
