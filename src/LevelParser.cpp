#include "LevelParser.h"
#include "TextureManager.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "Game.h"
#include "config.h"
#include "objectParser.h"
#include "vendor/base64.h"
#include <zlib.h>

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
	std::vector<int> layerRow(m_iWidth);
	std::string decodedIDs;
	uLongf numGids;
	TiXmlElement* dataNode;

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
	numGids = m_iWidth * m_iHeight * sizeof(int);
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

	for (int rows = 0; rows < m_iHeight; rows++) {
		for (int cols = 0; cols < m_iWidth; cols++) {
			data[rows][cols] = gids[rows * m_iWidth + cols];
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
