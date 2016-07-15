#include "Player.h"
#include "InputHandler.h"
#include <iostream>

void Player::handleInput() {
	int xAxisValue, yAxisValue;
	InputHandler* handlerInstance = InputHandler::Instance();
	if (handlerInstance->joysticksInitialised()) {
		xAxisValue = handlerInstance->stickXValue(0, LEFT_STICK);
		yAxisValue = handlerInstance->stickYValue(0, LEFT_STICK);
		if (xAxisValue > 0 || xAxisValue < 0) {
			m_velocity.setX(1 * xAxisValue);
		}
		if (yAxisValue > 0 || yAxisValue < 0) {
			m_velocity.setY(1 * yAxisValue);
		}
	}
}

void Player::update() {
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();
	SDLDrawable::update();
}
