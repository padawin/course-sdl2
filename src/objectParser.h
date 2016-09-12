#ifndef __objectParser__
#define __objectParser__

#include <tinyxml.h>
#include <vector>
#include <map>
#include "GameObject.h"
#include "SDLDrawable.h"

namespace objectParser {

bool parseObject(
	TiXmlElement* object,
	std::vector<GameObject*> *objects,
	std::vector<SDLDrawable*> *drawables
);
SDLDrawable* _createDrawable(TiXmlElement* object, std::map<std::string, std::string> properties);
void _parseProperties(TiXmlElement* object, std::map<std::string, std::string> *propertiesMap);

}
#endif
