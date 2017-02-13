#include "ObjectLayer.h"
#include <iostream>

void ObjectLayer::update() {
	m_objects.update();
}
void ObjectLayer::render() {
	m_objects.render();
}

GameObjectCollection* ObjectLayer::getObjects() {
	return &m_objects;
}
