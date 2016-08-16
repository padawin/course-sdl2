#include "GameObjectFactory.h"
#include <iostream>

static GameObjectFactory* s_pInstance;

GameObjectFactory::GameObjectFactory() {}
GameObjectFactory::~GameObjectFactory() {}

/**
 * Classic singleton method to get the GameObjectFactory instance.
 */
GameObjectFactory *GameObjectFactory::Instance() {
	if (s_pInstance == 0) {
		s_pInstance = new GameObjectFactory();
	}

	return s_pInstance;
}

void GameObjectFactory::clean() {
	for(std::map<std::string, GameObjectCreator*>::iterator itr = m_creators.begin(); itr != m_creators.end(); itr++) {
		delete itr->second;
	}
}

void GameObjectFactory::free() {
	Instance()->clean();
	delete s_pInstance;
	s_pInstance = 0;
}

bool GameObjectFactory::registerType(std::string typeID, GameObjectCreator* pCreator) {
	std::map<std::string, GameObjectCreator*>::iterator it = m_creators.find(typeID);

	// if the type is already registered, do nothing
	if (it != m_creators.end()) {
		delete pCreator;
		return false;
	}

	m_creators[typeID] = pCreator;
	return true;
}

GameObject* GameObjectFactory::create(std::string typeID) {
	std::map<std::string, GameObjectCreator*>::iterator it = m_creators.find(typeID);
	if (it == m_creators.end()) {
		std::cout << "could not find type: " << typeID << "\n";
		return NULL;
	}

	GameObjectCreator* pCreator = (*it).second;
	return pCreator->createGameObject();
}
