#ifndef __LevelParser__
#define __LevelParser__

#include <tinyxml.h>
#include <vector>
#include "Level.h"

class LevelParser {
	private:
	void _parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void _parseTileLayer(
		TiXmlElement* pTileElement,
		std::vector<Layer*> *pLayers,
		const std::vector<Tileset>* pTilesets
	);

	int m_iTileSize;
	int m_iWidth;
	int m_iHeight;

	public:
	virtual Level* parseLevel(const char* levelFile);
};

#endif

