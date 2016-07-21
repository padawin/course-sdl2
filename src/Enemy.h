#ifndef __Enemy__
#define __Enemy__

#include "SDLDrawable.h"
#include "GameObjectCreator.h"

class Enemy : public SDLDrawable {
};

// ENEMY BASE CREATOR CLASS

class EnemyCreator : public GameObjectCreator {
	GameObject* createGameObject() const;
};

#endif
