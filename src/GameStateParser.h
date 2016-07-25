#ifndef __GameStateParser__
#define __GameStateParser__

#include <vector>
#include "GameObject.h"
#include "SDLDrawable.h"
#include <libconfig.h++>

class GameStateParser {
	private:
	SDLDrawable* _parseDrawable(libconfig::Setting* objectSetting, std::string type);
	bool _parseObjects(
		libconfig::Setting &stateSetting,
		std::vector<GameObject*> *objects,
		std::vector<SDLDrawable*> *drawables
	);

	public:
	bool parseState(
		const char *stateFile,
		const char* stateID,
		std::vector<GameObject*> *objects,
		std::vector<SDLDrawable*> *drawables
	);
};

#endif
