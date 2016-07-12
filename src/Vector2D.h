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

	// Vector operations
	Vector2D operator+(const Vector2D& v2) const;
	Vector2D operator-(const Vector2D& v2) const;
	Vector2D operator*(float scalar);
	Vector2D operator/(float scalar);

	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*=(Vector2D& v, float scalar);
	friend Vector2D& operator/=(Vector2D& v, float scalar);
};

#endif
