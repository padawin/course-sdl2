#include "LevelParser.h"

Level* LevelParser::parseLevel(const char *levelFile) {
	// create a TinyXML document and load the map XML
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFile);

	// create the level object
	Level* level = new Level();

	// get the root node
	TiXmlElement* root = levelDocument.RootElement();

	root->Attribute("tilewidth", &m_iTileSize);
	root->Attribute("width", &m_iWidth);
	root->Attribute("height", &m_iHeight);

	for (TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		// parse the tilesets
		if (e->Value() == std::string("tileset")) {
			_parseTilesets(e, level->getTilesets());
		}

		// parse any object layers
		if (e->Value() == std::string("layer")) {
			_parseTileLayer(e, level->getLayers(), level->getTilesets());
		}
	}

	return level;
}

void LevelParser::_parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets) {

}

void LevelParser::_parseTileLayer(
	TiXmlElement* pTileElement,
	std::vector<Layer*> *pLayers,
	const std::vector<Tileset>* pTilesets
) {

}
