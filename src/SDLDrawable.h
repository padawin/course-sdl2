#ifndef __SDLDrawable__
#define __SDLDrawable__

#include <string>
#include <SDL2/SDL.h>
#include "GameObject.h"
#include "Vector2D.h"

/**
 * A SDLDrawable is a game object having a physical existence (eg can be
 * drawn). So it has a texture, a dimension, a position, a velocity and
 * an acceleration. It has some frames and a position in an animation
 * (currentRow and currentFrame).
 */
class SDLDrawable : public GameObject {
	protected:
	std::string m_sTextureID = "";
	int m_iNbFrames = 0;
	int m_iAnimationSpeed = 1;
	int m_iCurrentFrame = 0;
	int m_iCurrentRow = 0;

	bool m_bAnimated = false;

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_iWidth = 0;
	int m_iHeight = 0;

	public:
	SDLDrawable();

	/**
	 * Method to load the object
	 */
	virtual void load(const float x, const float y, const int width, const int height);
	void setTexture(const std::string textureID, const int nbFrames=1, const int animationSpeed=1);
	virtual void setAnimationSpeed(const int animationSpeed);
	virtual void setTextureRow(const int currentRow);
	virtual void setVelocity(const Vector2D velocity);
	virtual void setAcceleration(const Vector2D acceleration);
	virtual void setAnimated(const bool animated);

	virtual void update();
	virtual void render(SDL_Renderer* pRenderer);
};

#endif
