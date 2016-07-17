#include "PlayState.h"
#include <iostream>

const std::string PlayState::s_menuID = "PLAY";

void PlayState::update() {
	// nothing for now
}
void PlayState::render() {
	// nothing for now
}
bool PlayState::onEnter() {
	std::cout << "entering PlayState\n";
	return true;
}
bool PlayState::onExit() {
	std::cout << "exiting PlayState\n";
	return true;
}

std::string PlayState::getStateID() const {
	return s_menuID;
}
