#ifndef __GameState__
#define __GameState__

#include <string>
#include <vector>
#include "GameObject.h"
#include "SDLDrawable.h"

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
	std::vector<GameObject*> m_vGameObjects = {};
	std::vector<SDLDrawable*> m_vRenderableObjects = {};

	public:
	virtual	~GameState() {}
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual std::string getStateID() const = 0;
};

#endif
