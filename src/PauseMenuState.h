#ifndef __PauseMenuState__
#define __PauseMenuState__

#include "MenuState.h"
#include "MenuButton.h"

class PauseMenuState : public MenuState {
	protected:
	static const std::string s_menuID;

	public:
	PauseMenuState();
	MenuButton* createButton(const int index);
	std::string getStateID() const;

	static void resumeGame();
	static void goToMainMenu();
	static void quitGame();
};

#endif

