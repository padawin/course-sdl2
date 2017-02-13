#ifndef __Player__
#define __Player__

#include "SDLDrawable.h"
#include "GameObjectCreator.h"

class Player : public SDLDrawable {
	private:
	void handleInput();

	public:
	void update();
};

// PLAYER BASE CREATOR CLASS

class PlayerCreator : public GameObjectCreator {
	GameObject* createGameObject() const;
};

#endif
