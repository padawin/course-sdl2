#include "ServiceProvider.h"

static UserActions* s_userActions;

UserActions* ServiceProvider::getUserActions() {
	return s_userActions;
}

void ServiceProvider::setUserActions() {
	free(s_userActions);
	s_userActions = new UserActions();
	Command pauseJoystick;
	pauseJoystick.type = CONTROLLER_BUTTON;
	pauseJoystick.buttonId = 7;
	s_userActions->add("PAUSE", pauseJoystick);
	Command pauseKeyboard;
	pauseKeyboard.type = KEYBOARD_KEY;
	pauseKeyboard.key = SDL_SCANCODE_ESCAPE;
	s_userActions->add("PAUSE", pauseKeyboard);

	Command menuNextJoystick;
	menuNextJoystick.type = CONTROLLER_STICK;
	menuNextJoystick.stickAxis = LEFT_STICK_Y;
	menuNextJoystick.stickDirection = 1;
	s_userActions->add("CHANGE_MENU_NEXT", menuNextJoystick);
	Command menuNextKeyboard;
	menuNextKeyboard.type = KEYBOARD_KEY;
	menuNextKeyboard.key = SDL_SCANCODE_DOWN;
	s_userActions->add("CHANGE_MENU_NEXT", menuNextKeyboard);

	Command menuPreviousJoystick;
	menuPreviousJoystick.type = CONTROLLER_STICK;
	menuPreviousJoystick.stickAxis = LEFT_STICK_Y;
	menuPreviousJoystick.stickDirection = -1;
	s_userActions->add("CHANGE_MENU_PREVIOUS", menuPreviousJoystick);
	Command menuPreviousKeyboard;
	menuPreviousKeyboard.type = KEYBOARD_KEY;
	menuPreviousKeyboard.key = SDL_SCANCODE_UP;
	s_userActions->add("CHANGE_MENU_PREVIOUS", menuPreviousKeyboard);

	Command activateMenuButtonJoystick;
	activateMenuButtonJoystick.type = CONTROLLER_BUTTON;
	activateMenuButtonJoystick.buttonId = 0;
	s_userActions->add("ACTIVATE_MENU_BUTTON", activateMenuButtonJoystick);
	Command activateMenuButtonKeyboard;
	activateMenuButtonKeyboard.type = KEYBOARD_KEY;
	activateMenuButtonKeyboard.key = SDL_SCANCODE_RETURN;
	s_userActions->add("ACTIVATE_MENU_BUTTON", activateMenuButtonKeyboard);

	Command movePlayerUpJoystick;
	movePlayerUpJoystick.type = CONTROLLER_STICK;
	movePlayerUpJoystick.stickAxis = LEFT_STICK_Y;
	movePlayerUpJoystick.stickDirection = -1;
	s_userActions->add("MOVE_PLAYER_UP", movePlayerUpJoystick);
	Command movePlayerUpKeyboard;
	movePlayerUpKeyboard.type = KEYBOARD_KEY;
	movePlayerUpKeyboard.key = SDL_SCANCODE_UP;
	s_userActions->add("MOVE_PLAYER_UP", movePlayerUpKeyboard);

	Command movePlayerDownJoystick;
	movePlayerDownJoystick.type = CONTROLLER_STICK;
	movePlayerDownJoystick.stickAxis = LEFT_STICK_Y;
	movePlayerDownJoystick.stickDirection = 1;
	s_userActions->add("MOVE_PLAYER_DOWN", movePlayerDownJoystick);
	Command movePlayerDownKeyboard;
	movePlayerDownKeyboard.type = KEYBOARD_KEY;
	movePlayerDownKeyboard.key = SDL_SCANCODE_DOWN;
	s_userActions->add("MOVE_PLAYER_DOWN", movePlayerDownKeyboard);

	Command movePlayerLeftJoystick;
	movePlayerLeftJoystick.type = CONTROLLER_STICK;
	movePlayerLeftJoystick.stickAxis = LEFT_STICK_X;
	movePlayerLeftJoystick.stickDirection = -1;
	s_userActions->add("MOVE_PLAYER_LEFT", movePlayerLeftJoystick);
	Command movePlayerLeftKeyboard;
	movePlayerLeftKeyboard.type = KEYBOARD_KEY;
	movePlayerLeftKeyboard.key = SDL_SCANCODE_LEFT;
	s_userActions->add("MOVE_PLAYER_LEFT", movePlayerLeftKeyboard);

	Command movePlayerRightJoystick;
	movePlayerRightJoystick.type = CONTROLLER_STICK;
	movePlayerRightJoystick.stickAxis = LEFT_STICK_X;
	movePlayerRightJoystick.stickDirection = 1;
	s_userActions->add("MOVE_PLAYER_RIGHT", movePlayerRightJoystick);
	Command movePlayerRightKeyboard;
	movePlayerRightKeyboard.type = KEYBOARD_KEY;
	movePlayerRightKeyboard.key = SDL_SCANCODE_RIGHT;
	s_userActions->add("MOVE_PLAYER_RIGHT", movePlayerRightKeyboard);

	Command playerRushJoystick;
	playerRushJoystick.type = CONTROLLER_BUTTON;
	playerRushJoystick.buttonId = 1;
	s_userActions->add("PLAYER_RUSH", playerRushJoystick);
}

void ServiceProvider::clean() {
	free(s_userActions);
	s_userActions = 0;
}
