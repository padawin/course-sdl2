#include "LevelParser.h"
#include "TextureManager.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "Game.h"
#include "objectParser.h"
#include "base64.h"
#include <zlib.h>

LevelParser::LevelParser() :
	m_iTileSize(0),
	m_iWidth(0),
	m_iHeight(0)
{}

std::string LevelParser::_joinPath(std::string pathPart1, std::string pathPart2) {
	return pathPart1 + '/' + pathPart2;
}

Level* LevelParser::parseLevel(std::string levelFilePath) {
	// create a TinyXML document and load the map XML
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(levelFilePath);

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

		if (e->Value() == std::string("properties")) {
			_parseTextures(e);
		}
	}

	for (TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		// parse any object layers
		if(e->Value() == std::string("objectgroup") || e->Value() == std::string("layer")) {
			if (e->FirstChildElement()->Value() == std::string("object")) {
				_parseObjectLayer(e, level->getLayers());
			}
			else if (e->FirstChildElement()->Value() ==std::string("data")) {
				_parseTileLayer(e, level->getLayers(), level->getTilesets());
			}
		}
	}

	return level;
}

void LevelParser::_parseTextures(TiXmlElement* propertiesNode) {
	for (TiXmlElement* e = propertiesNode->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() != std::string("property")) {
			continue;
		}

		TextureManager::Instance()->load(
			_joinPath(RESOURCE_PATH, e->Attribute("value")),
			e->Attribute("name"),
			Game::Instance()->getRenderer()
		);
	}
}

void LevelParser::cleanLevel(Level* level) {
	delete level;
	level = 0;
}

void LevelParser::_parseTilesets(TiXmlElement* tilesetRoot, std::vector<Tileset>* tilesets) {
	std::string fileName = tilesetRoot->FirstChildElement()->Attribute("source");
	std::string textureFile = _joinPath(RESOURCE_PATH, fileName);

	// first add the tileset to texture manager
	TextureManager::Instance()->load(
		textureFile,
		tilesetRoot->Attribute("name"),
		Game::Instance()->getRenderer()
	);

	// // create a tileset object
	Tileset tileset;
	tilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
	tilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
	tilesetRoot->Attribute("firstgid", &tileset.firstGridID);
	tilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	tilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	tilesetRoot->Attribute("spacing", &tileset.spacing);
	tilesetRoot->Attribute("margin", &tileset.margin);

	tileset.name = tilesetRoot->Attribute("name");
	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	tilesets->push_back(tileset);
}

void LevelParser::_parseTileLayer(
	TiXmlElement* tileElement,
	std::vector<Layer*> *layers,
	const std::vector<Tileset>* tilesets
) {
	TileLayer* tileLayer = new TileLayer(m_iTileSize, *tilesets);

	// tile data
	std::vector<std::vector<int>> data;
	std::vector<int> layerRow((size_t) m_iWidth);
	std::string decodedIDs;
	uLongf numGids;
	TiXmlElement* dataNode = 0;

	for (TiXmlElement* e = tileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("data")) {
			dataNode = e;
		}
	}

	for (TiXmlNode* e = dataNode->FirstChild(); e != NULL; e = e->NextSibling()) {
		TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	// uncompress zlib compression
	numGids = (uLongf) (m_iWidth * m_iHeight * (int) sizeof(int));
	std::vector<unsigned> gids(numGids);

	uncompress(
		(Bytef*) &gids[0],
		&numGids,
		(const Bytef*) decodedIDs.c_str(),
		decodedIDs.size()
	);

	for (int j = 0; j < m_iHeight; j++) {
		data.push_back(layerRow);
	}

	unsigned long rows, cols,
		height = (unsigned long) m_iHeight,
		width = (unsigned long) m_iWidth;
	for (rows = 0; rows < height; rows++) {
		for (cols = 0; cols < width; cols++) {
			data[rows][cols] = (int) gids[rows * width + cols];
		}
	}

	tileLayer->setTileIDs(data, m_iWidth, m_iHeight);
	layers->push_back(tileLayer);
}

void LevelParser::_parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *layers) {
	// create an object layer
	ObjectLayer* pObjectLayer = new ObjectLayer();
	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		if (e->Value() != std::string("object")) {
			continue;
		}

		objectParser::parseObject(
			e,
			pObjectLayer->getObjects()->getGameObjects(),
			pObjectLayer->getObjects()->getDrawables()
		);
	}
	layers->push_back(pObjectLayer);
}
