#include "Level.h"

std::vector<Tileset>* Level::getTilesets() {
	return &m_vTilesets;
}

std::vector<Layer*>* Level::getLayers() {
	return &m_vLayers;
}
