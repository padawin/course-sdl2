#include "TileLayer.h"
#include "Game.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) :
	m_iNbColumns(0),
	m_iNbRows(0),
	m_iLayerNbColumns(0),
	m_iLayerNbRows(0),
	m_iTileSize(tileSize),
	m_position(0, 0),
	m_velocity(0, 0),
	m_vTilesets(tilesets),
	m_vTileIDs()
{
	m_iNbColumns = Game::Instance()->getScreenWidth() / m_iTileSize + 1;
	m_iNbRows = Game::Instance()->getScreenHeight() / m_iTileSize + 1;
}

void TileLayer::setTileIDs(const std::vector<std::vector<int>>& data, int width, int height) {
	m_vTileIDs = data;

	m_iLayerNbColumns = width;
	m_iLayerNbRows = height;
	if (m_iNbRows > height) {
		m_iNbRows = height;
	}

	if (m_iNbColumns > width) {
		m_iNbColumns = width;
	}
}

void TileLayer::setTileSize(int tileSize) {
	m_iTileSize = tileSize;
}

void TileLayer::update() {
}

void TileLayer::render() {
	int x, y, x2, y2 = 0;

	// what is the first visible tile in the layer
	x = (int) m_position.getX() / m_iTileSize;
	y = (int) m_position.getY() / m_iTileSize;

	// Where is the edge of the screen in the first tile
	x2 = int(m_position.getX()) % m_iTileSize;
	y2 = int(m_position.getY()) % m_iTileSize;

	for (int i = 0; i < m_iNbRows; i++) {
		for (int j = 0; j < m_iNbColumns; j++) {
			int id = _getTileId(j + x, i + y);
			if (id == 0) {
				continue;
			}

			Tileset tileset = _getTilesetByID(id);
			TextureManager::Instance()->drawTile(
				tileset.name, tileset.margin, tileset.spacing,
				(j * m_iTileSize) - x2, (i * m_iTileSize) - y2,
				m_iTileSize, m_iTileSize,
				1 + (id - tileset.firstGridID) / tileset.numColumns,
				(id - tileset.firstGridID) % tileset.numColumns,
				Game::Instance()->getRenderer()
			);
		}
	}
}

Tileset TileLayer::_getTilesetByID(int tileID) {
	size_t sizeTilesets = m_vTilesets.size();
	for (unsigned int i = 0; i < sizeTilesets; i++) {
		// if we reached the last tileset, return it
		if (i == sizeTilesets - 1) {
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

int TileLayer::_getTileId(int x, int y) {
	if (x < 0 || x >= m_iLayerNbColumns) {
		return 0;
	}

	if (y < 0 || y >= m_iLayerNbRows) {
		return 0;
	}

	return m_vTileIDs[(unsigned long) y][(unsigned long) x];
}
