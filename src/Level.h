#ifndef __Level__
#define __Level__

#include <vector>
#include <string>
#include "Layer.h"

struct Tileset {
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};

class Level {
	private:
	std::vector<Tileset> m_vTilesets;
	std::vector<Layer*> m_vLayers;

	public:
	Level();
	~Level() {}
	void update();
	void render();
	std::vector<Tileset>* getTilesets();
	std::vector<Layer*>* getLayers();
};

#endif
