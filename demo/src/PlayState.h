#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"
#include "Level.h"

/**
 * State for the in game screen. Contains a player and a list of enemies
 */
class PlayState : public GameState {
	private:
	static const std::string s_menuID;

	Level *m_level = 0;

	void _initActors(const char* actorsFilePath);
	void _cleanActors();

	public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const;
};

#endif
