#include "objectParser.h"
#include "GameObjectFactory.h"

namespace objectParser {

bool parseObject(
	TiXmlElement* object,
	std::vector<GameObject*> *objects,
	std::vector<SDLDrawable*> *drawables
) {
	std::string type;
	std::map<std::string, std::string> properties;
	std::map<std::string, std::string>::iterator typeIter;

	_parseProperties(object, &properties);
	typeIter = properties.find("type");
	if (typeIter == properties.end()) {
		return false;
	}

	type = typeIter->second;
	if (properties.find("drawable") != properties.end()) {
		SDLDrawable* drawableObject = _createDrawable(object, properties);
		drawables->push_back(drawableObject);
		objects->push_back(drawableObject);
	}
	else {
		GameObject* gameObject = GameObjectFactory::Instance()->create(type);
		objects->push_back(gameObject);
	}

	return true;
}

SDLDrawable* _createDrawable(TiXmlElement* object, std::map<std::string, std::string> properties) {
	std::string texture, type;
	std::map<std::string, std::string>::iterator propertyIterator;
	float x, y;
	int w, h,
		textureRow = 0,
		nbFrames = 1,
		animationSpeed = 1;
	bool animated = false;

	nbFrames = 1;
	object->QueryFloatAttribute("x", &x);
	object->QueryFloatAttribute("y", &y);
	object->QueryIntAttribute("width", &w);
	object->QueryIntAttribute("height", &h);

	texture = properties.find("texture")->second;
	type = properties.find("type")->second;
	textureRow = atoi(properties.find("textureRow")->second.c_str());

	propertyIterator = properties.find("nbFrames");
	if (propertyIterator != properties.end()) {
		nbFrames = atoi(propertyIterator->second.c_str());
	}

	propertyIterator = properties.find("animationSpeed");
	if (propertyIterator != properties.end()) {
		animationSpeed = atoi(propertyIterator->second.c_str());
	}

	propertyIterator = properties.find("animated");
	animated = propertyIterator != properties.end() && propertyIterator->second == "true";

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

void _parseProperties(TiXmlElement* object, std::map<std::string, std::string> *propertiesMap) {
	// get the property values
	for (
		TiXmlElement* properties = object->FirstChildElement();
		properties != NULL;
		properties = properties->NextSiblingElement()
	) {
		if (properties->Value() != std::string("properties")) {
			continue;
		}

		for (
			TiXmlElement* property = properties->FirstChildElement();
			property != NULL;
			property = property->NextSiblingElement()
		) {
			if (property->Value() != std::string("property")) {
				continue;
			}

			std::string name, value;
			name = property->Attribute("name");
			value = property->Attribute("value");
			(*propertiesMap)[name] = value;
		}
	}
}

}
