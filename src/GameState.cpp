#include "GameState.h"
#include "Game.h"

void GameState::update() {
	m_objects.update();
}

void GameState::render() {
	m_objects.render();
}

bool GameState::onExit() {
	m_objects.clean();
	return true;
}
