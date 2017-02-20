#include "MainMenuState.h"
#include "SDL2_framework/Game.h"
#include "PlayState.h"

const std::string MainMenuState::s_menuID = "MAINMENU";

MainMenuState::MainMenuState() : MenuState::MenuState(2) {
	s_vActions.push_back(MainMenuState::startGame);
	s_vActions.push_back(MainMenuState::quitGame);
}

std::string MainMenuState::getStateID() const {
	return s_menuID;
}

void MainMenuState::startGame() {
	Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::quitGame() {
	Game::Instance()->quit();
}
