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
SDLDrawable* _parseDrawable(TiXmlElement* object, std::string type);

}
#endif
