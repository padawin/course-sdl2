#include "Player.h"
#include "InputHandler.h"

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

void Player::update() {
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();
	SDLDrawable::update();
}
