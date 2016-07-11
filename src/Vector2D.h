#ifndef __Vector2D__
#define __Vector2D__

class Vector2D {
	protected:
	float m_iX;
	float m_iY;

	public:
	Vector2D(const float x, const float y);
	float getLength();
	float getX();
	float getY();
	void setX(const float x);
	void setY(const float y);
};

#endif
