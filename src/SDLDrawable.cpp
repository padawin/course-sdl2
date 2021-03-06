#include "SDLDrawable.h"
#include "TextureManager.h"

SDLDrawable::SDLDrawable() :
	m_position(Vector2D()),
	m_velocity(Vector2D()),
	m_acceleration(Vector2D()) {}

void SDLDrawable::load(SDLDrawableLoader* loader) {
	m_position.setX(loader->getX());
	m_position.setY(loader->getY());
	m_iWidth = loader->getWidth();
	m_iHeight = loader->getHeight();
	setTexture(
		loader->getTextureID(),
		loader->getNbFrames(),
		loader->getAnimationSpeed()
	);
	setTextureRow(loader->getTextureRow());
	setAnimated(loader->isAnimated());
}

void SDLDrawable::setTexture(const std::string textureID, const unsigned int nbFrames, const unsigned int animationSpeed) {
	m_iCurrentRow = 1;
	m_iCurrentFrame = 1;
	setAnimationSpeed(animationSpeed);
	setAnimated(nbFrames > 1);
	m_iNbFrames = nbFrames;
	m_sTextureID = textureID;
}

void SDLDrawable::setAnimationSpeed(const unsigned int animationSpeed) {
	m_iAnimationSpeed = animationSpeed;
}

void SDLDrawable::setAnimated(const bool animated) {
	m_bAnimated = animated;
	if (!m_bAnimated) {
		m_iCurrentFrame = 1;
	}
}

void SDLDrawable::setTextureRow(const int currentRow) {
	m_iCurrentRow = currentRow;
}

void SDLDrawable::setVelocity(const Vector2D velocity) {
	m_velocity = velocity;
}

void SDLDrawable::setAcceleration(const Vector2D acceleration) {
	m_acceleration = acceleration;
}

void SDLDrawable::update() {
	if (m_bAnimated) {
		unsigned int timePerFrame = 1000 / m_iAnimationSpeed;
		m_iCurrentFrame = int(((SDL_GetTicks() / timePerFrame) % m_iNbFrames));
	}
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void SDLDrawable::render(SDL_Renderer* pRenderer) {
	TextureManager::Instance()->drawFrame(
		m_sTextureID,
		(int) m_position.getX(), (int) m_position.getY(),
		m_iWidth, m_iHeight,
		m_iCurrentRow, m_iCurrentFrame,
		pRenderer
	);
}

// SDLDRAWABLELOADER

SDLDrawableLoader::SDLDrawableLoader(
	const float x, const float y,
	const int width, const int height,
	const std::string textureID,
	const int textureRow
) :
	m_fX(x),
	m_fY(y),
	m_iWidth(width),
	m_iHeight(height),
	m_sTextureID(textureID),
	m_iTextureRow(textureRow) {}

SDLDrawableLoader::SDLDrawableLoader(
	const float x, const float y,
	const int width, const int height,
	const std::string textureID, const int textureRow,
	const unsigned int nbFrames, const unsigned int animationSpeed,
	const bool animated
) : SDLDrawableLoader(x, y, width, height, textureID, textureRow) {
	m_iNbFrames = nbFrames;
	m_iAnimationSpeed = animationSpeed;
	m_bAnimated = animated;
}

float SDLDrawableLoader::getX() {
	return m_fX;
}

float SDLDrawableLoader::getY() {
	return m_fY;
}

int SDLDrawableLoader::getWidth() {
	return m_iWidth;
}

int SDLDrawableLoader::getHeight() {
	return m_iHeight;
}

std::string SDLDrawableLoader::getTextureID() {
	return m_sTextureID;
}

int SDLDrawableLoader::getTextureRow() {
	return m_iTextureRow;
}

unsigned int SDLDrawableLoader::getNbFrames() {
	return m_iNbFrames;
}

unsigned int SDLDrawableLoader::getAnimationSpeed() {
	return m_iAnimationSpeed;
}

bool SDLDrawableLoader::isAnimated() {
	return m_bAnimated;
}
