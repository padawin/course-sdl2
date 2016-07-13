#include "Player.h"

void Player::update() {
	SDLDrawable::update();
	m_position.setX(m_position.getX() + 5);
}
