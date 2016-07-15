#ifndef __Vector2D__
#define __Vector2D__

enum Vector2DCoord {VECTOR_X, VECTOR_Y};

class Vector2D {
	protected:
	float m_iX;
	float m_iY;

	public:
	Vector2D();
	Vector2D(const float x, const float y);
	float getLength();
	float getX();
	float getY();
	void set(Vector2DCoord coord, const float value);
	void setX(const float x);
	void setY(const float y);

	void normalize();

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
