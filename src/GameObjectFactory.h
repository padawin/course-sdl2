#ifndef __GameObjectFactory__
#define __GameObjectFactory__

#include <string>
#include <map>
#include "GameObject.h"
#include "GameObjectCreator.h"

class GameObjectFactory {
	private:
	/**
	 * The game object factory is a singleton, so its constructor and
	 * destructor are private
	 */
	GameObjectFactory();
	~GameObjectFactory();

	std::map<std::string, GameObjectCreator*> m_creators;

	public:
	/**
	 * Because of the singleton, the following construct and operator are
	 * removed.
	 */
	GameObjectFactory(GameObjectFactory const&) = delete;
	void operator=(GameObjectFactory const&) = delete;

	/**
	 * Method to get the game object factory instance.
	 */
	static GameObjectFactory* Instance();

	/**
	 * Method to clean the map of object creators
	 */
	void clean();

	/**
	 * Method to free the factory.
	 */
	static void free();

	/**
	 * Method to register a game object type
	 */
	bool registerType(std::string typeID, GameObjectCreator* pCreator);

	/**
	 * Method to instanciate a game object based on its type id
	 */
	GameObject* create(std::string typeID);
};

#endif
