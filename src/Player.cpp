#include "Player.h"
#include "ServiceProvider.h"

/**
 * The joystick button and sticks states are checked. If the button 1 (B on
 * xbox controller) is pressed, the player's speed is increased (it makes him
 * run), if the left stick is tilted in any direction, the player's velocity is
 * set.
 */
void Player::handleInput() {
	int movesUp, movesDown, movesLeft, movesRight;
	float velocityBasis = 1.0;
	UserActions* userActions = ServiceProvider::getUserActions();

	if (userActions->getActionState("PLAYER_RUSH")) {
		velocityBasis = 2.5;
		setAnimationSpeed(15);
	}
	else {
		setAnimationSpeed(10);
	}

	movesUp = userActions->getActionState("MOVE_PLAYER_UP");
	movesDown = userActions->getActionState("MOVE_PLAYER_DOWN");
	movesLeft = userActions->getActionState("MOVE_PLAYER_LEFT");
	movesRight = userActions->getActionState("MOVE_PLAYER_RIGHT");
	if (movesLeft) {
		m_velocity.setX(velocityBasis * -1);
		setAnimated(true);
	}
	else if (movesRight) {
		m_velocity.setX(velocityBasis);
		setAnimated(true);
	}

	if (movesUp) {
		m_velocity.setY(velocityBasis * -1);
		setAnimated(true);
	}
	else if (movesDown) {
		m_velocity.setY(velocityBasis);
		setAnimated(true);
	}
}

/**
 * Reset the player velocity and update the input even polling and the player
 */
void Player::update() {
	setAnimated(false);
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();
	SDLDrawable::update();
}

// PLAYER BASE CREATOR CLASS

GameObject* PlayerCreator::createGameObject() const {
	return new Player();
}
