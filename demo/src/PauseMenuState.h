#ifndef __PauseMenuState__
#define __PauseMenuState__

#include "MenuState.h"
#include "MenuButton.h"

/**
 * State for the pause menu
 */
class PauseMenuState : public MenuState {
	protected:
	static const std::string s_menuID;

	public:
	PauseMenuState();
	std::string getStateID() const;

	static void resumeGame();
	static void goToMainMenu();
	static void quitGame();
};

#endif

