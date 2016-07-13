#include "Enemy.h"

void Enemy::update() {
	SDLDrawable::update();
	m_position.setX(m_position.getX() + 3);
}
