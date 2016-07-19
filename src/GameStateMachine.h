#ifndef __GameStateMachine__
#define __GameStateMachine__

#include "GameState.h"
#include <vector>

class GameStateMachine {
	private:
	std::vector<GameState*> m_vGameStates = {};

	public:
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	bool popState();
	void clean();
	GameState* getCurrentState();

	void update();
	void render();
};

#endif
