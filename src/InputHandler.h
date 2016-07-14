#ifndef __InputHandler__
#define __InputHandler__

#include <SDL2/SDL_joystick.h>
#include <vector>

class InputHandler {
	private:
	InputHandler();
	std::vector<SDL_Joystick*> m_joysticks;
	bool m_bJoysticksInitialised;

	public:
	static InputHandler* Instance();
	static void free();
	bool update();
	void clean();
	void initialiseJoysticks();
	bool joysticksInitialised();
};

#endif
