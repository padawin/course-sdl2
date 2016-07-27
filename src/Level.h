#ifndef __Level__
#define __Level__

#include <vector>
#include <string>

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

	public:
	Level();
	~Level() {}
	void update();
	void render();
	std::vector<Tileset>* getTilesets();
};

#endif
