#ifndef __GameObject__
#define __GameObject__

#include <string>
#include <SDL2/SDL.h>

class GameObject {
	public:
	virtual ~GameObject() {}
	virtual void update() = 0;
};

#endif
