#ifndef __UserActions__
#define __UserActions__

#include <string>
#include <map>
#include <vector>
#include "InputHandler.h"

struct Command {
	InputType type;
	int id;
	JoystickControl stickAxis;
};

class UserActions {
	protected:
	std::map<std::string, std::vector<Command>> m_mMappings;

	public:
	UserActions();
	void add(std::string name, Command c);
	int getActionState(std::string name);
};

#endif
