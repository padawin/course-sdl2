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
		}

		xAxisValue = (float) handlerInstance->stickXValue(0, LEFT_STICK);
		yAxisValue = (float) handlerInstance->stickYValue(0, LEFT_STICK);
		if (xAxisValue > 0 || xAxisValue < 0) {
			m_velocity.setX(velocityBasis * xAxisValue);
		}
		if (yAxisValue > 0 || yAxisValue < 0) {
			m_velocity.setY(velocityBasis * yAxisValue);
		}
	}
}

/**
 * Reset the player velocity and update the input even polling and the player
 */
void Player::update() {
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();
	SDLDrawable::update();
}
