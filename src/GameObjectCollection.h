#ifndef __GameObjectCollection__
#define __GameObjectCollection__

#include <vector>
#include "GameObject.h"
#include "SDLDrawable.h"

class GameObjectCollection {
	private:
	std::vector<GameObject*> m_vGameObjects = {};
	std::vector<SDLDrawable*> m_vRenderableObjects = {};

	public:
	virtual void update();
	virtual void render();
	virtual void clean();
	virtual std::vector<GameObject*>* getGameObjects();
	virtual std::vector<SDLDrawable*>* getDrawables();
};

#endif
