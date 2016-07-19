#ifndef __MenuState__
#define __MenuState__

#include "GameState.h"
#include "MenuButton.h"
#include <vector>

class MenuState : public GameState {
	protected:
	std::vector<MenuButton*> m_vButtons = {};
	int m_iNbButtons;
	int m_iActiveButtonIndex = 0;
	bool m_bMenuBeingChanged = false;
	std::vector<void (*)()> s_vActions = {};

	public:
	MenuState(const int nbButtons);
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual MenuButton* createButton(const int index) = 0;
};

#endif
