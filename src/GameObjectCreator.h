#ifndef __GameObjectCreator__
#define __GameObjectCreator__

class GameObjectCreator {
	public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~GameObjectCreator() {}
};

#endif
