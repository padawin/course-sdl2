#ifndef __Enemy__
#define __Enemy__

#include "SDL2_framework/SDLDrawable.h"
#include "SDL2_framework/GameObjectCreator.h"

class Enemy : public SDLDrawable {
};

// ENEMY BASE CREATOR CLASS

class EnemyCreator : public GameObjectCreator {
	GameObject* createGameObject() const;
};

#endif
