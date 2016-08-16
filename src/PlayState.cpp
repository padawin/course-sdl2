#include "PlayState.h"
#include "PauseMenuState.h"
#include "InputHandler.h"
#include "Game.h"
#include "GameStateParser.h"
#include "LevelParser.h"

const std::string PlayState::s_menuID = "PLAY";

/**
 * If the button 7 of the joystick is pressed (start in xbox controller), push
 * the pause menu state, to pause the game.
 *
 * Then/else, update every object of the play state (player and enemies).
 */
void PlayState::update() {
	InputHandler* handlerInstance = InputHandler::Instance();
	if (handlerInstance->joysticksInitialised() && InputHandler::Instance()->getButtonState(0, 7)) {
		Game::Instance()->getStateMachine()->pushState(new PauseMenuState());
	}

	for (std::vector<GameObject*>::size_type i = 0; i != m_vGameObjects.size(); i++) {
		m_vGameObjects[i]->update();
	}
}
void PlayState::render() {
	m_level->render();
	for (std::vector<GameObject*>::size_type i = 0; i != m_vRenderableObjects.size(); i++) {
		m_vRenderableObjects[i]->render(Game::Instance()->getRenderer());
	}
}
bool PlayState::onEnter() {
	LevelParser levelParser;
	m_level = levelParser.parseLevel("resources/levels/", "level1.tmx");
	_initActors();
	return true;
}
bool PlayState::onExit() {
	_cleanActors();
	LevelParser levelParser;
	levelParser.cleanLevel(m_level);
	return true;
}

std::string PlayState::getStateID() const {
	return s_menuID;
}

void PlayState::_initActors() {
	// parse the state
	GameStateParser stateParser;
	stateParser.parseState(
		"configs/levels.cfg",
		getStateID().c_str(),
		&m_vGameObjects,
		&m_vRenderableObjects
	);
}

void PlayState::_cleanActors() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_vGameObjects.size(); i++) {
		delete m_vGameObjects[i];
		m_vGameObjects[i] = NULL;
		m_vRenderableObjects[i] = NULL;
	}

	m_vGameObjects.clear();
}
