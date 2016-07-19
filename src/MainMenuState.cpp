#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"

const std::string MainMenuState::s_menuID = "MAINMENU";

MainMenuState::MainMenuState() : MenuState::MenuState(2) {
	s_vActions.push_back(MainMenuState::startGame);
	s_vActions.push_back(MainMenuState::quitGame);
}

MenuButton* MainMenuState::createButton(const int index) {
	MenuButton* b = new MenuButton();
	float y = 15;
	y += (float) (100 * (index + 1));
	b->load(50.0, y, 300, 100);
	b->setTexture("mainmenu", 1);
	b->setTextureRow(index + 1);
	b->setActive(index == m_iActiveButtonIndex);
	b->setAction(s_vActions[index]);

	return b;
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
