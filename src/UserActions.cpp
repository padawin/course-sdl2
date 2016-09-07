#include "UserActions.h"

UserActions::UserActions() : m_mMappings({}) {}

void UserActions::add(std::string name, Command c) {
	if (!m_mMappings.count(name)) {
		std::vector<Command> tempCommands;
		m_mMappings[name] = tempCommands;
	}

	m_mMappings[name].push_back(c);
}

int UserActions::getActionState(std::string name) {
	if (!m_mMappings.count(name)) {
		return 0;
	}

	std::vector<Command> commands = m_mMappings[name];
	int ret = 0;
	InputHandler* handlerInstance = InputHandler::Instance();
	for (unsigned int c = 0; c < commands.size(); c++) {
		switch (commands[c].type) {
			case CONTROLLER_BUTTON:
				ret = !handlerInstance->joysticksInitialised() ? 0 :
					handlerInstance->getButtonState(0, commands[c].buttonId);
				break;
			case CONTROLLER_STICK:
				ret = !handlerInstance->joysticksInitialised() ? 0 :
					handlerInstance->stickValue(0, commands[c].stickAxis);
				break;
			case KEYBOARD_KEY:
				ret = handlerInstance->getKeyState(commands[c].key);
				break;
		}

		if (ret != 0) {
			break;
		}
	}

	return ret;
}

void UserActions::resetActionState(std::string name) {
	if (!m_mMappings.count(name)) {
		return;
	}

	std::vector<Command> commands = m_mMappings[name];
	InputHandler* handlerInstance = InputHandler::Instance();
	for (unsigned int c = 0; c < commands.size(); c++) {
		switch (commands[c].type) {
			case CONTROLLER_BUTTON:
				if (handlerInstance->joysticksInitialised()) {
					handlerInstance->setButtonState(
						0, commands[c].buttonId, false
					);
				}
				break;
			case KEYBOARD_KEY:
				handlerInstance->setKeyState(commands[c].key, false);
				break;
		}
	}
}
