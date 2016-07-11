#ifndef __SDLDrawable__
#define __SDLDrawable__

#include <string>
#include <SDL2/SDL.h>
#include "GameObject.h"

class SDLDrawable : public GameObject {
	protected:
	std::string m_sTextureID;
	int m_iNbFrames;
	int m_iCurrentFrame;
	int m_iCurrentRow;
	int m_iX;
	int m_iY;
	int m_iWidth;
	int m_iHeight;

	public:
	SDLDrawable();
	virtual void load(const int x, const int y, const int width, const int height);
	virtual void setTexture(const std::string textureID, int nbFrames);
	virtual void setTextureRow(const int currentRow);
	virtual void update();
	virtual void render(SDL_Renderer* pRenderer);
};

#endif
