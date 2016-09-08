#ifndef __UserActions__
#define __UserActions__

#include <string>
#include <map>
#include <vector>
#include "InputHandler.h"

struct Command {
	InputType type;
	int buttonId;
	int stickDirection = 0;
	JoystickControl stickAxis;
	SDL_Scancode key;
};

class UserActions {
	protected:
	std::map<std::string, std::vector<Command>> m_mMappings;

	public:
	UserActions();
	void add(std::string name, Command c);
	int getActionState(std::string name);
	void resetActionState(std::string name);
};

#endif
