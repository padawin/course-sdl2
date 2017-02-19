#ifndef __Player__
#define __Player__

#include "SDL2_framework/SDLDrawable.h"
#include "SDL2_framework/GameObjectCreator.h"

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
