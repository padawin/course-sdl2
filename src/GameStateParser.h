#ifndef __GameStateParser__
#define __GameStateParser__

#include <vector>
#include "GameObject.h"
#include "SDLDrawable.h"
#include <tinyxml.h>

class GameStateParser {
	private:
	bool _getStateNode(TiXmlElement** root, const char* stateID);

	public:
	bool parseState(
		const char* stateFile,
		std::vector<GameObject*> *objects,
		std::vector<SDLDrawable*> *drawables,
		const char* stateID = 0
	);
};

#endif
