#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) : m_vTilesets(tilesets) {
	m_iTileSize = tileSize;
}

void TileLayer::setTileIDs(const std::vector<std::vector<int>>& data) {
	m_vTileIDs = data;
}

void TileLayer::setTileSize(int tileSize) {
	m_iTileSize = tileSize;
}

void TileLayer::update() {

}

void TileLayer::render() {

}
