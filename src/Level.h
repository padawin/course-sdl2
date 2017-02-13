#ifndef __Level__
#define __Level__

#include <vector>
#include <string>
#include "Layer.h"

struct Tileset {
	int firstGridID = 0;
	int tileWidth = 0;
	int tileHeight = 0;
	int spacing = 0;
	int margin = 0;
	int width = 0;
	int height = 0;
	int numColumns = 0;
	std::string name = "";
};

class Level {
	private:
	std::vector<Tileset> m_vTilesets;
	std::vector<Layer*> m_vLayers;

	// Only a level parser can create a level
	friend class LevelParser;
	Level();

	public:
	// @TODO Must free the layers
	~Level();
	void update();
	void render();
	std::vector<Tileset>* getTilesets();
	std::vector<Layer*>* getLayers();
};

#endif
