#ifndef __MenuState__
#define __MenuState__

#include "GameState.h"
#include "MenuButton.h"
#include <vector>

/**
 * State representing a menu. A menu has a vector of buttons, a number of
 * buttons, the index of the currently active button, a list of actions
 * (associated with the buttons) and a flag to know if the menu is being
 * changed (eg if the currently selected item is changed to another one)
 */
class MenuState : public GameState {
	protected:
	std::string m_sConfigFile = "";
	std::vector<MenuButton*> m_vButtons = {};
	unsigned int m_iNbButtons;
	unsigned int m_iActiveButtonIndex = 0;
	bool m_bMenuBeingChanged = false;
	std::vector<void (*)()> s_vActions = {};

	public:
	MenuState(const unsigned int nbButtons);
	virtual void update();
	virtual bool onEnter();
	virtual bool onExit();
};

#endif
