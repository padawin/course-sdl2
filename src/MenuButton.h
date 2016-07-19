#ifndef __MenuButton__
#define __MenuButton__

#include "SDLDrawable.h"

class MenuButton : public SDLDrawable {
	protected:
	bool m_bActive = false;
	void (*m_callback)() = NULL;

	public:
	void setActive(const bool active);
	void setAction(void (*callback)());
	void executeAction();
};

#endif
