#ifndef __InputHandler__
#define __InputHandler__

#include <SDL2/SDL_joystick.h>
#include <vector>
#include "Vector2D.h"

class InputHandler {
	private:
	InputHandler();
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D, Vector2D>> m_joystickAxisValues;
	bool m_bJoysticksInitialised;
	const int M_JOYSTICK_DEADZONE = 10000;
	const int M_LEFT_STICK_X_AXIS = 0;
	const int M_LEFT_STICK_Y_AXIS = 1;
	const int M_RIGHT_STICK_X_AXIS = 3;
	const int M_RIGHT_STICK_Y_AXIS = 4;

	public:
	static InputHandler* Instance();
	static void free();
	bool update();
	void clean();
	void initialiseJoysticks();
	bool joysticksInitialised();
	int xValue(int joy, int stick);
	int yValue(int joy, int stick);
};

#endif
