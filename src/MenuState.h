#ifndef __MenuState__
#define __MenuState__

#include "GameState.h"
#include "MenuButton.h"
#include <vector>

class MenuState : public GameState {
	protected:
	std::vector<MenuButton*> m_buttons = {};
	int m_nbButtons;
	int m_activeButtonIndex = 0;
	bool m_menuBeingChanged = false;
	std::vector<void (*)()> s_pActions = {};

	public:
	MenuState(const int nbButtons);
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual MenuButton* createButton(const int index) = 0;
};

#endif
