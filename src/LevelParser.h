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
	std::string _joinPath(std::string pathPart1, std::string pathPart2);

	int m_iTileSize;
	int m_iWidth;
	int m_iHeight;

	public:
	virtual Level* parseLevel(std::string levelsDir, std::string levelFile);
};

#endif

