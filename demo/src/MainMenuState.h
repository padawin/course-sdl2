#ifndef __MainMenuState__
#define __MainMenuState__

#include "MenuState.h"
#include "MenuButton.h"

/**
 * State to display the main menu.
 */
class MainMenuState : public MenuState {
	protected:
	static const std::string s_menuID;

	public:
	MainMenuState();
	std::string getStateID() const;

	static void startGame();
	static void quitGame();
};

#endif

