#ifndef __TileLayer__
#define __TileLayer__

#include <vector>
#include "Level.h"
#include "Layer.h"
#include "Vector2D.h"

class TileLayer : public Layer {
	private:
	int m_iNbColumns;
	int m_iNbRows;
	int m_iTileSize;
	Vector2D m_position;
	Vector2D m_velocity;
	const std::vector<Tileset> &m_vTilesets;
	std::vector<std::vector<int>> m_vTileIDs;

	Tileset getTilesetByID(int tileID);

	public:
	TileLayer(int tileSize, const std::vector<Tileset> &tilesets);
	virtual void update();
	virtual void render();
	void setTileIDs(const std::vector<std::vector<int>>& data);
	void setTileSize(int tileSize);
};

#endif
