#include "NoJoystickState.h"
#include <iostream>

const std::string NoJoystickState::s_menuID = "NO_JOYSTICK";

void NoJoystickState::update() {
	// nothing for now
}
void NoJoystickState::render() {
	// nothing for now
}
bool NoJoystickState::onEnter() {
	std::cout << "entering NoJoystickState\n";
	return true;
}
bool NoJoystickState::onExit() {
	std::cout << "exiting NoJoystickState\n";
	return true;
}

std::string NoJoystickState::getStateID() const {
	return s_menuID;
}
