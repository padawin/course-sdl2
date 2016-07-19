#include "NoJoystickState.h"
#include "Game.h"
#include "InputHandler.h"

const std::string NoJoystickState::s_menuID = "NO_JOYSTICK";

void NoJoystickState::update() {
	if (InputHandler::Instance()->joysticksInitialised()) {
		Game::Instance()->getStateMachine()->popState();
	}
}
void NoJoystickState::render() {
	// nothing for now
}
bool NoJoystickState::onEnter() {
	return true;
}
bool NoJoystickState::onExit() {
	return true;
}

std::string NoJoystickState::getStateID() const {
	return s_menuID;
}
