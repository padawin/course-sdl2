#ifndef __MenuButton__
#define __MenuButton__

#include "SDLDrawable.h"

class MenuButton : public SDLDrawable {
	protected:
	bool m_pActive;

	public:
	void setActive(const bool active);
};

#endif
