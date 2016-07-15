#ifndef __InputHandler__
#define __InputHandler__

#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>
#include <vector>
#include "Vector2D.h"

enum JoystickControl {LEFT_STICK, RIGHT_STICK};

class InputHandler {
	private:
	InputHandler();
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D, Vector2D>> m_joystickAxisValues;
	std::vector<std::vector<bool>> m_buttonStates;
	bool m_bJoysticksInitialised;
	const int M_JOYSTICK_DEADZONE = 10000;
	const int M_LEFT_STICK_X_AXIS = 0;
	const int M_LEFT_STICK_Y_AXIS = 1;
	const int M_RIGHT_STICK_X_AXIS = 3;
	const int M_RIGHT_STICK_Y_AXIS = 4;

	void setJoystickValue(const int value, Vector2D* axisVector, Vector2DCoord coord);
	void handleStickEvent(const SDL_Event event);
	void handleButtonEvent(const SDL_Event event, const bool isDown);

	public:
	static InputHandler* Instance();
	static void free();
	bool update();
	void clean();
	void initialiseJoysticks();
	bool joysticksInitialised();
	int stickXValue(const int joy, const JoystickControl stick);
	int stickYValue(const int joy, const JoystickControl stick);
	bool getButtonState(int joy, int buttonNumber);
};

#endif
