#ifndef __ObjectLayer__
#define __ObjectLayer__

#include <vector>
#include "Layer.h"
#include "GameObject.h"
#include "GameObjectCollection.h"

class ObjectLayer : public Layer {
	private:
	GameObjectCollection m_objects;

	public:
	virtual void update();
	virtual void render();

	GameObjectCollection* getObjects();
};

#endif
