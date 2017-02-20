#include "Enemy.h"

// ENEMY BASE CREATOR CLASS

GameObject* EnemyCreator::createGameObject() const {
	return new Enemy();
}
