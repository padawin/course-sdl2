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
	m_position += m_velocity;
}

void TileLayer::render() {
	int x, y, x2, y2 = 0;

	// what is the first visible tile in the layer
	x = m_position.getX() / m_iTileSize;
	y = m_position.getY() / m_iTileSize;

	// Where is the edge of the screen in the first tile
	x2 = int(m_position.getX()) % m_iTileSize;
	y2 = int(m_position.getY()) % m_iTileSize;

	for (int i = 0; i < m_iNbRows; i++) {
		for (int j = 0; j < m_iNbColumns; j++) {
			int id = m_vTileIDs[i][j + x];
			if (id == 0) {
				continue;
			}

			Tileset tileset = getTilesetByID(id);
			id--;
			TextureManager::Instance()->drawTile(
				tileset.name, 2, 2,
				(j * m_iTileSize) - x2, (i * m_iTileSize) - y2,
				m_iTileSize, m_iTileSize,
				(id - (tileset.firstGridID - 1)) / tileset.numColumns,
				(id - (tileset.firstGridID - 1)) % tileset.numColumns,
				Game::Instance()->getRenderer()
			);
		}
	}
}

Tileset TileLayer::getTilesetByID(int tileID) {
	for (int i = 0; i < m_vTilesets.size(); i++) {
		// if we reached the last tileset, return it
		if (i == m_vTilesets.size() - 1) {
			return m_vTilesets[i];
		}

		// otherwise, check if the id is within the curent tileset's ids
		if (
			tileID >= m_vTilesets[i].firstGridID
			&& tileID < m_vTilesets[i + 1].firstGridID
		) {
			return m_vTilesets[i];
		}
	}

	// did not find tileset, returning empty tileset
	Tileset t;
	return t;
}
