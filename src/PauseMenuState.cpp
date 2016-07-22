#include "PauseMenuState.h"
#include "Game.h"
#include "InputHandler.h"
#include "MainMenuState.h"

const std::string PauseMenuState::s_menuID = "PAUSEMENU";

PauseMenuState::PauseMenuState() : MenuState::MenuState(3) {
	s_vActions.push_back(PauseMenuState::resumeGame);
	s_vActions.push_back(PauseMenuState::goToMainMenu);
	s_vActions.push_back(PauseMenuState::quitGame);
}

MenuButton* PauseMenuState::createButton(const int index) {
	MenuButton* b = new MenuButton();
	float y = 15;
	y += (float) (100 * (index + 1));
	b->load(SDLDrawableLoader(50.0, y, 300, 100, "pausemenu", index + 1));
	b->setActive(index == m_iActiveButtonIndex);
	b->setAction(s_vActions[index]);

	return b;
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
