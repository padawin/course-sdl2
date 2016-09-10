#include "GameObjectCollection.h"
#include "Game.h"

void GameObjectCollection::update() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_vGameObjects.size(); i++) {
		m_vGameObjects[i]->update();
	}
}

void GameObjectCollection::render() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_vRenderableObjects.size(); i++) {
		m_vRenderableObjects[i]->render(Game::Instance()->getRenderer());
	}
}

void GameObjectCollection::clean() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_vGameObjects.size(); i++) {
		delete m_vGameObjects[i];
	}
	m_vGameObjects.clear();
	m_vRenderableObjects.clear();
}

std::vector<GameObject*>* GameObjectCollection::getGameObjects() {
	return &m_vGameObjects;
}

std::vector<SDLDrawable*>* GameObjectCollection::getDrawables() {
	return &m_vRenderableObjects;
}
