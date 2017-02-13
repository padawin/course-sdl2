#ifndef __MenuButton__
#define __MenuButton__

#include "SDLDrawable.h"
#include "GameObjectCreator.h"

/**
 * SDLDrawable representing buttons in MenuStates, it has an action.
 */
class MenuButton : public SDLDrawable {
	protected:
	void (*m_callback)() = NULL;

	public:
	void setActive(const bool active);
	void setAction(void (*callback)());
	void executeAction();
};

// MENU BUTTON BASE CREATOR CLASS

class MenuButtonCreator : public GameObjectCreator {
	GameObject* createGameObject() const;
};

#endif
