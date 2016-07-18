#ifndef __MenuButton__
#define __MenuButton__

#include "SDLDrawable.h"

class MenuButton : public SDLDrawable {
	protected:
	bool m_pActive;
	void (*m_callback)();

	public:
	void setActive(const bool active);
	void setAction(void (*callback)());
	void executeAction();
};

#endif
