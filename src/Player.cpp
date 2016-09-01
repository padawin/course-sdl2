#include "Player.h"
#include "InputHandler.h"

/**
 * The joystick button and sticks states are checked. If the button 1 (B on
 * xbox controller) is pressed, the player's speed is increased (it makes him
 * run), if the left stick is tilted in any direction, the player's velocity is
 * set.
 */
void Player::handleInput() {
	float xAxisValue, yAxisValue, velocityBasis = 1.0;
	InputHandler* handlerInstance = InputHandler::Instance();

	if (handlerInstance->joysticksInitialised()) {
		if (handlerInstance->getButtonState(0, 1)) {
			velocityBasis = 2.5;
			setAnimationSpeed(15);
		}
		else {
			setAnimationSpeed(10);
		}

		xAxisValue = (float) handlerInstance->stickValue(0, LEFT_STICK_X);
		yAxisValue = (float) handlerInstance->stickValue(0, LEFT_STICK_Y);
		if (xAxisValue > 0 || xAxisValue < 0) {
			m_velocity.setX(velocityBasis * xAxisValue);
			setAnimated(true);
		}

		if (yAxisValue > 0 || yAxisValue < 0) {
			m_velocity.setY(velocityBasis * yAxisValue);
			setAnimated(true);
		}
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
