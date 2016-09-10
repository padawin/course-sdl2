#include "GameState.h"
#include "Game.h"

void GameState::update() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_vGameObjects.size(); i++) {
		m_vGameObjects[i]->update();
	}
}

void GameState::render() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_vRenderableObjects.size(); i++) {
		m_vRenderableObjects[i]->render(Game::Instance()->getRenderer());
	}
}

bool GameState::onExit() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_vGameObjects.size(); i++) {
		delete m_vGameObjects[i];
	}
	m_vGameObjects.clear();
	m_vRenderableObjects.clear();
	return true;
}
