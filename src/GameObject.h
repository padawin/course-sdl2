#ifndef __GameObject__
#define __GameObject__

#include <string>
#include <SDL2/SDL.h>

class GameObject {
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
	virtual ~GameObject();
	virtual void load(const int x, const int y, const int width, const int height);
	virtual void setTexture(const std::string textureID, int nbFrames);
	virtual void setTextureRow(const int currentRow);
	virtual void update();
	virtual void render(SDL_Renderer* pRenderer);
	virtual void clean();
};

#endif
