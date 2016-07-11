#include "SDLDrawable.h"
#include "TextureManager.h"

SDLDrawable::SDLDrawable() {}

void SDLDrawable::load(const int x, const int y, const int width, const int height) {
	m_iX = x;
	m_iY = y;
	m_iWidth = width;
	m_iHeight = height;
}

void SDLDrawable::setTexture(const std::string textureID, int nbFrames) {
	m_iCurrentRow = 1;
	m_iCurrentFrame = 1;
	m_iNbFrames = nbFrames;
	m_sTextureID = textureID;
}

void SDLDrawable::setTextureRow(const int currentRow) {
	m_iCurrentRow = currentRow;
}

void SDLDrawable::update() {
	m_iCurrentFrame = int(((SDL_GetTicks() / 100) % m_iNbFrames));
}

void SDLDrawable::render(SDL_Renderer* pRenderer) {
	TextureManager::Instance()->drawFrame(
		m_sTextureID,
		m_iX, m_iY,
		m_iWidth, m_iHeight,
		m_iCurrentRow, m_iCurrentFrame,
		pRenderer
	);
}
