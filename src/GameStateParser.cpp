#include "GameStateParser.h"
#include <iostream>

using namespace libconfig;

bool GameStateParser::parseState(
	const char *stateFile,
	const char* stateID,
	std::vector<GameObject*> *objects,
	std::vector<SDLDrawable*> *drawables
) {
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

	Setting &root = cfg.getRoot();
	if (!root.exists(stateID)) {
		std::cerr << "No state " << stateID << " entry found in "
			<< stateFile << std::endl;
		return false;
	}

	_parseObjects(root[stateID], objects, drawables);
	return true;
}

bool GameStateParser::_parseObjects(
	Setting &stateSetting,
	std::vector<GameObject*> *objects,
	std::vector<SDLDrawable*> *drawables
) {
	if (!stateSetting.exists("objects")) {
		return false;
	}


	return true;
}
