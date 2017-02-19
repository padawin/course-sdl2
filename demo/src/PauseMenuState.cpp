#include "PauseMenuState.h"
#include "SDL2_framework/Game.h"
#include "MainMenuState.h"

const std::string PauseMenuState::s_menuID = "PAUSEMENU";

PauseMenuState::PauseMenuState() : MenuState::MenuState(3) {
	s_vActions.push_back(PauseMenuState::resumeGame);
	s_vActions.push_back(PauseMenuState::goToMainMenu);
	s_vActions.push_back(PauseMenuState::quitGame);
}

std::string PauseMenuState::getStateID() const {
	return s_menuID;
}

void PauseMenuState::resumeGame() {
	Game::Instance()->getStateMachine()->popState();
}

void PauseMenuState::goToMainMenu() {
	Game::Instance()->getStateMachine()->clean();
	Game::Instance()->getStateMachine()->pushState(new MainMenuState());
}

void PauseMenuState::quitGame() {
	Game::Instance()->quit();
}
