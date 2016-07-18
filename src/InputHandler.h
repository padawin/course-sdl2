#ifndef __InputHandler__
#define __InputHandler__

#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>
#include <vector>
#include <map>
#include "Vector2D.h"

enum JoystickControl {LEFT_STICK, RIGHT_STICK};

class InputHandler {
	private:
	InputHandler();
	// store each joystick in a vector of pairs, the first element of the pair
	// being the joystick id and the second element, the joystick itself
	std::vector<std::pair<int, SDL_Joystick*>> m_joysticks;
	// map joysticks ids and pairs of stick values (one element per stick, each
	// stick has a value per axis (x and y)
	std::map<int, std::pair<Vector2D, Vector2D>> m_joystickAxisValues;
	// map joysticks ids and buttons state, each joystick has a list of buttons
	// set to true or false depending on if the button is pressed
	std::map<int, std::vector<bool>> m_buttonStates;
	bool m_bJoysticksInitialised;
	const int M_JOYSTICK_DEADZONE = 10000;
	const int M_LEFT_STICK_X_AXIS = 0;
	const int M_LEFT_STICK_Y_AXIS = 1;
	const int M_RIGHT_STICK_X_AXIS = 3;
	const int M_RIGHT_STICK_Y_AXIS = 4;

	void setJoystickValue(const int value, Vector2D* axisVector, Vector2DCoord coord);
	void handleStickEvent(const SDL_Event event);
	void handleButtonEvent(const SDL_Event event, const bool isDown);
	void handleJoystickRemoved(const SDL_Event event);

	public:
	static InputHandler* Instance();
	static void free();
	bool update();
	void clean();
	void initialiseJoystick(const int index);
	bool joysticksInitialised();
	int stickXValue(const int joy, const JoystickControl stick);
	int stickYValue(const int joy, const JoystickControl stick);
	bool getButtonState(int joy, int buttonNumber);
};

#endif
