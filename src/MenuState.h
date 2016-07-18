#ifndef __MenuState__
#define __MenuState__

#include "GameState.h"
#include "MenuButton.h"
#include <vector>

class MenuState : public GameState {
	private:
	static const std::string s_menuID;
	std::vector<MenuButton*> m_buttons = {};
	int m_nbButtons = 0;
	bool m_activeButtonIndex = 0;
	bool m_menuBeingChanged = false;

	public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const;

	static void startGame();
	static void quitGame();
};

#endif

