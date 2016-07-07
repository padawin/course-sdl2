#include "GameObject.h"

void GameObject::load(const int x, const int y, const int width, const int height) {
	m_iX = x;
	m_iY = y;
	m_iWidth = width;
	m_iHeight = height;
}

void GameObject::setTexture(const std::string textureID, int nbFrames) {
	m_iCurrentRow = 1;
	m_iCurrentFrame = 1;
	m_iNbFrames = nbFrames;
	m_sTextureID = textureID;
}

void GameObject::update() {

}

void GameObject::render() {

}

void GameObject::clean() {

}

