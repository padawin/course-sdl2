#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"
#include "Player.h"
#include "Enemy.h"

/**
 * State for the in game screen. Contains a player and a list of enemies
 */
class PlayState : public GameState {
	private:
	static const std::string s_menuID;
	std::vector<Enemy*> m_enemies = {};
	Player* m_player = NULL;

	void _initActors();
	void _cleanActors();

	public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const;
};

#endif

