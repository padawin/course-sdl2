#include "PlayState.h"
#include "PauseMenuState.h"
#include "Game.h"
#include "GameStateParser.h"
#include "LevelParser.h"
#include "ServiceProvider.h"

const std::string PlayState::s_menuID = "PLAY";

/**
 * If the button 7 of the joystick is pressed (start in xbox controller), push
 * the pause menu state, to pause the game.
 *
 * Then/else, update every object of the play state (player and enemies).
 */
void PlayState::update() {
	m_level->update();
	if (ServiceProvider::getUserActions()->getActionState("PAUSE")) {
		Game::Instance()->getStateMachine()->pushState(new PauseMenuState());
	}

	GameState::update();
}

void PlayState::render() {
	m_level->render();
	GameState::render();
}

bool PlayState::onEnter() {
	LevelParser levelParser;
	m_level = levelParser.parseLevel("configs/levels/level1.tmx");
	return true;
}

bool PlayState::onExit() {
	GameState::onExit();
	LevelParser levelParser;
	levelParser.cleanLevel(m_level);
	return true;
}

std::string PlayState::getStateID() const {
	return s_menuID;
}
