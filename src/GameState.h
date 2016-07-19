#ifndef __GameState__
#define __GameState__

#include <string>
#include <vector>
#include "GameObject.h"
#include "SDLDrawable.h"

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
