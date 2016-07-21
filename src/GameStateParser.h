#ifndef __GameStateParser__
#define __GameStateParser__

#include <vector>
#include "GameObject.h"
#include <libconfig.h++>

class GameStateParser {
	public:
	bool parseState(const char* stateFile, const char* stateID, std::vector<GameObject*> *pObjects);

	private:
	void _parseObjects(libconfig::Setting* objectsSetting, std::vector<GameObject*> *pObjects);
};

#endif
