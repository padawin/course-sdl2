#include "PlayState.h"
#include "PauseMenuState.h"
#include "InputHandler.h"
#include "Game.h"
#include <iostream>

const std::string PlayState::s_menuID = "PLAY";

void PlayState::update() {
	InputHandler* handlerInstance = InputHandler::Instance();
	if (handlerInstance->joysticksInitialised() && InputHandler::Instance()->getButtonState(0, 7)) {
		Game::Instance()->getStateMachine()->pushState(new PauseMenuState());
	}

	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}
void PlayState::render() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_renderableObjects.size(); i++) {
		m_renderableObjects[i]->render(Game::Instance()->getRenderer());
	}
}
bool PlayState::onEnter() {
	std::cout << "entering PlayState\n";
	_initActors();
	return true;
}
bool PlayState::onExit() {
	std::cout << "exiting PlayState\n";
	_cleanActors();
	return true;
}

std::string PlayState::getStateID() const {
	return s_menuID;
}

void PlayState::_initActors() {
	m_player = new Player();
	m_gameObjects.push_back(m_player);
	m_renderableObjects.push_back(m_player);
	m_player->load(0.0, 0.0, 128, 142);
	m_player->setTexture("animate", 6);

	int l_iNbEnemies = 4;
	for (int e = 0; e < l_iNbEnemies; ++e) {
		m_enemies.push_back(new Enemy());
		m_gameObjects.push_back(m_enemies[e]);
		m_renderableObjects.push_back(m_enemies[e]);
		m_enemies[e]->load(0.0, (float) (142 * (e + 1)), 128, 142);
		m_enemies[e]->setTexture("animate", 6);
	}
}

void PlayState::_cleanActors() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
		delete m_gameObjects[i];
		m_gameObjects[i] = NULL;
	}

	m_gameObjects.clear();
}
