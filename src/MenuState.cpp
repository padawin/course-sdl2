#include "MenuState.h"
#include "Game.h"
#include <iostream>

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() {
	// nothing for now
}
void MenuState::render() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_renderableObjects.size(); i++) {
		m_renderableObjects[i]->render(Game::Instance()->getRenderer());
	}
}
bool MenuState::onEnter() {
	std::cout << "entering MenuState\n";
	m_nbButtons = 2;
	m_activeButtonIndex = 0;
	for (int i = 0; i < m_nbButtons; ++i) {
		m_buttons.push_back(new MenuButton());
		m_gameObjects.push_back(m_buttons[i]);
		m_renderableObjects.push_back(m_buttons[i]);
		m_buttons[i]->load(100, 100 * (i + 1), 300, 100);
		m_buttons[i]->setTexture("mainmenu", 1);
		m_buttons[i]->setTextureRow(i + 1);
		m_buttons[i]->setActive(i == m_activeButtonIndex);
	}
	return true;
}
bool MenuState::onExit() {
	std::cout << "exiting MenuState\n";
	return true;
}

std::string MenuState::getStateID() const {
	return s_menuID;
}
