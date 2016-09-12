#include "GameStateParser.h"
#include "objectParser.h"
#include <iostream>

bool GameStateParser::parseState(
	const char* stateFile,
	std::vector<GameObject*> *objects,
	std::vector<SDLDrawable*> *drawables,
	const char* stateID
) {
	// create a TinyXML document and load the map XML
	TiXmlDocument stateDocument;
	stateDocument.LoadFile(stateFile);

	TiXmlElement* root = stateDocument.RootElement();
	// a state ID is provided, consider the file as a list of states, the good
	// one must be found
	if (stateID != 0 && !_getStateNode(&root, stateID)) {
		std::cerr << "No state found with ID " << stateID << std::endl;
		return false;
	}

	for (TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		// parse the objects
		if (e->Value() == std::string("object")) {
			objectParser::parseObject(e, objects, drawables);
		}
	}

	return true;
}

bool GameStateParser::_getStateNode(TiXmlElement** root, const char* stateID) {
	for (TiXmlElement* e = (*root)->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		// find the required state node
		if (e->Value() == std::string("state") && strcmp(e->Attribute("id"), stateID) == 0) {
			(*root) = e->FirstChildElement();
			return true;
		}
	}

	return false;
}
