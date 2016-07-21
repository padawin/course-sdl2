#include "GameStateParser.h"
#include <iostream>

using namespace libconfig;

bool GameStateParser::parseState(const char *stateFile, const char* stateID, std::vector<GameObject *> *pObjects) {
	Config cfg;

	try {
		cfg.readFile(stateFile);
	}
	catch (const FileIOException &e) {
		std::cerr << "I/O error while reading file." << std::endl;
		return false;
	}
	catch (const ParseException &e) {
		std::cerr << "Parse error at " << e.getFile() << ":" << e.getLine()
			<< " - " << e.getError() << std::endl;
		return false;
	}

	const Setting &root = cfg.getRoot();
	if (!root.exists(stateID)) {
		std::cerr << "No state " << stateID << " entry found in "
			<< stateFile << std::endl;
	}

	const Setting &states = root[stateID];
	if (states.exists("objects")) {
		_parseObjects(&states["objects"], pObjects);
	}

	return true;
}

void GameStateParser::_parseObjects(Setting* objectsSetting, std::vector<GameObject*> *pObjects) {

}
