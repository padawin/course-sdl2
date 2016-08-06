#include "TileLayer.h"
#include "Game.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) :
	m_iTileSize(tileSize), m_vTilesets(tilesets), m_position(0, 0), m_velocity(0, 0)
{
	m_iNbColumns = Game::Instance()->getScreenWidth() / m_iTileSize;
	m_iNbRows = Game::Instance()->getScreenHeight() / m_iTileSize;
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
