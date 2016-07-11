#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D(const float x, const float y) {
	m_iX = x;
	m_iY = y;
}

float Vector2D::getLength() {
	return sqrt(pow(m_iX, 2) + pow(m_iY, 2));
}

float Vector2D::getX() {
	return m_iX;
}
float Vector2D::getY() {
	return m_iY;
}

void Vector2D::setX(const float x) {
	m_iX = x;
}

void Vector2D::setY(const float y) {
	m_iY = y;
}

