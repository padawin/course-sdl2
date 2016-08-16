#include "Level.h"

Level::Level() {

}

Level::~Level() {
	for (int l = 0; l < (int) m_vLayers.size(); l++) {
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
	for (int i = 0; i < m_vLayers.size(); i++) {
		m_vLayers[i]->render();
	}
}

void Level::update() {
	for (int i = 0; i < m_vLayers.size(); i++) {
		m_vLayers[i]->update();
	}
}
