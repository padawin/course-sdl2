#ifndef __Player__
#define __Player__

#include "SDLDrawable.h"

class Player : public SDLDrawable {
	private:
	void handleInput();

	public:
	void update();
};

#endif
