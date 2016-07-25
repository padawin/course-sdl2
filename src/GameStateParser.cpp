#include "GameStateParser.h"
#include "GameObjectFactory.h"
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

	const Setting &objectsSetting = stateSetting["objects"];
	int count = objectsSetting.getLength();
	for (int i = 0; i < count; ++i) {
		bool drawable;
		std::string type;
		Setting &objectSetting = objectsSetting[i];
		objectSetting.lookupValue("drawable", drawable);
		objectSetting.lookupValue("type", type);

		if (drawable) {
			SDLDrawable* drawableObject = _parseDrawable(&objectSetting, type);
			drawables->push_back(drawableObject);
			objects->push_back(drawableObject);
		}
		else {
			GameObject* gameObject = GameObjectFactory::Instance()->create(type);
			objects->push_back(gameObject);
		}
	}

	return true;
}

SDLDrawable* GameStateParser::_parseDrawable(Setting* objectSetting, std::string type) {
	std::string texture;
	float x, y;
	int w, h, textureRow, nbFrames, animationSpeed;
	bool animated;

	nbFrames = 1;
	objectSetting->lookupValue("x", x);
	objectSetting->lookupValue("y", y);
	objectSetting->lookupValue("w", w);
	objectSetting->lookupValue("h", h);
	objectSetting->lookupValue("texture", texture);
	objectSetting->lookupValue("textureRow", textureRow);
	objectSetting->lookupValue("nbFrames", nbFrames);
	objectSetting->lookupValue("animationSpeed", animationSpeed);
	objectSetting->lookupValue("animated", animated);

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
