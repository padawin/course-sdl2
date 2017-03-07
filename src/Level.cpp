#include "Level.h"

Level::Level() : m_vTilesets(), m_vLayers() {

}

Level::~Level() {
	for (unsigned long l = 0; l < m_vLayers.size(); l++) {
		delete m_vLayers[l];
		m_vLayers[l] = 0;
	}
}

std::vector<Tileset>* Level::getTilesets() {
	return &m_vTilesets;
}

std::vector<Layer*>* Level::getLayers() {
	return &m_vLayers;
}

void Level::render() {
	size_t sizeLayers = m_vLayers.size();
	for (unsigned int i = 0; i < sizeLayers; i++) {
		m_vLayers[i]->render();
	}
}

void Level::update() {
	size_t sizeLayers = m_vLayers.size();
	for (unsigned int i = 0; i < sizeLayers; i++) {
		m_vLayers[i]->update();
	}
}
