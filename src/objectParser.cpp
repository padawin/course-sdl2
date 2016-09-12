#include "objectParser.h"
#include "GameObjectFactory.h"

namespace objectParser {

bool parseObject(
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

SDLDrawable* _parseDrawable(TiXmlElement* object, std::string type) {
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

}
