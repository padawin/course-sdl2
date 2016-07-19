#ifndef __MainMenuState__
#define __MainMenuState__

#include "MenuState.h"
#include "MenuButton.h"

class MainMenuState : public MenuState {
	protected:
	static const std::string s_menuID;

	public:
	MainMenuState();
	MenuButton* createButton(const int index);
	std::string getStateID() const;

	static void startGame();
	static void quitGame();
};

#endif

