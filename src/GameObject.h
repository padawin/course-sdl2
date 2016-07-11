#ifndef __GameObject__
#define __GameObject__

#include <string>
#include <SDL2/SDL.h>

class GameObject {
	public:
	virtual ~GameObject() {}
	virtual void load(const int x, const int y, const int width, const int height) = 0;
	virtual void setTexture(const std::string textureID, int nbFrames) = 0;
	virtual void setTextureRow(const int currentRow) = 0;
	virtual void update() = 0;
	virtual void render(SDL_Renderer* pRenderer) = 0;
};

#endif
