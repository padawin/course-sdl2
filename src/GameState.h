#ifndef __GameState__
#define __GameState__

#include <string>
#include "GameObjectCollection.h"

/**
 * Each scene is a game state, provided in the game state machine.
 * Each State has a list of objects and of renderable objects.
 *
 * Each state can be updated (at each game loop iteration), rendered, has an ID
 * (to differenciate it from another state) and has two hooks (one when the
 * machine enters the state and one when the machine leaves it).
 */
class GameState {
	protected:
	GameObjectCollection m_objects;

	public:
	virtual	~GameState() {}
	GameState() : m_objects() {}
	virtual void update();
	virtual void render();
	virtual bool onEnter() = 0;
	virtual bool onExit();
	virtual std::string getStateID() const = 0;
};

#endif
