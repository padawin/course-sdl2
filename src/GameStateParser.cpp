#include "GameStateParser.h"
#include "GameObjectFactory.h"
#include <iostream>

bool GameStateParser::parseState(
	const char *stateFile,
	const char* stateID,
	std::vector<GameObject*> *objects,
	std::vector<SDLDrawable*> *drawables
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
			_parseObject(e, objects, drawables);
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

bool GameStateParser::_parseObject(
	TiXmlElement* object,
	std::vector<GameObject*> *objects,
	std::vector<SDLDrawable*> *drawables
) {
	bool drawable;
	const char* type;
	drawable = object->Attribute("drawable");
	type = object->Attribute("type");

	if (drawable) {
		SDLDrawable* drawableObject = _parseDrawable(object, type);
		drawables->push_back(drawableObject);
		objects->push_back(drawableObject);
	}
	else {
		GameObject* gameObject = GameObjectFactory::Instance()->create(type);
		objects->push_back(gameObject);
	}

	return true;
}

SDLDrawable* GameStateParser::_parseDrawable(TiXmlElement* object, std::string type) {
	const char* texture;
	float x, y;
	int w, h,
		textureRow = 0,
		nbFrames = 1,
		animationSpeed = 1;
	bool animated = false;

	nbFrames = 1;
	object->QueryFloatAttribute("x", &x);
	object->QueryFloatAttribute("y", &y);
	object->QueryIntAttribute("w", &w);
	object->QueryIntAttribute("h", &h);
	texture = object->Attribute("texture");
	object->QueryIntAttribute("textureRow", &textureRow);
	object->QueryIntAttribute("nbFrames", &nbFrames);
	object->QueryIntAttribute("animationSpeed", &animationSpeed);
	object->QueryBoolAttribute("animated", &animated);

	SDLDrawableLoader* loader;
	// non animated texture
	if (nbFrames == 1) {
		loader = new SDLDrawableLoader(x, y, w, h, texture, textureRow);
	}
	else {
		loader = new SDLDrawableLoader(
			x, y, w, h,
			texture, textureRow,
			nbFrames, animationSpeed,
			animated
		);
	}

	SDLDrawable* gameObject = dynamic_cast<SDLDrawable*>(GameObjectFactory::Instance()->create(type));
	gameObject->load(loader);

	delete loader;
	loader = NULL;

	return gameObject;
}
