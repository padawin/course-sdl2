#ifndef __GameStateParser__
#define __GameStateParser__

#include <vector>
#include "GameObject.h"
#include "SDLDrawable.h"
#include <tinyxml.h>

class GameStateParser {
	private:
	SDLDrawable* _parseDrawable(TiXmlElement* object, std::string type);
	bool _parseObjects(
		TiXmlElement* object,
		std::vector<GameObject*> *objects,
		std::vector<SDLDrawable*> *drawables
	);
	bool _parseObject(
		TiXmlElement* object,
		std::vector<GameObject*> *objects,
		std::vector<SDLDrawable*> *drawables
	);
	bool _getStateNode(TiXmlElement** root, const char* stateID);

	public:
	bool parseState(
		const char *stateFile,
		const char* stateID,
		std::vector<GameObject*> *objects,
		std::vector<SDLDrawable*> *drawables
	);
};

#endif
