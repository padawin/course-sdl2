#include "InputHandler.h"
#include <iostream>
#include <SDL2/SDL.h>

static InputHandler* s_pInstance;

InputHandler::InputHandler() {}

InputHandler *InputHandler::Instance() {
	if (s_pInstance == 0) {
		s_pInstance = new InputHandler();
	}

	return s_pInstance;
}

bool InputHandler::update() {
	bool ret = true;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			ret = false;
		}
		else if (event.type == SDL_JOYAXISMOTION) {
			handleStickEvent(event);
		}
		else if (event.type == SDL_JOYBUTTONDOWN) {
			handleButtonEvent(event, true);
		}
		else if (event.type == SDL_JOYBUTTONUP) {
			handleButtonEvent(event, false);
		}
	}

	return ret;
}

void InputHandler::handleStickEvent(const SDL_Event event) {
	int whichOne = event.jaxis.which;
	// left stick move left or right
	if (event.jaxis.axis == M_LEFT_STICK_X_AXIS) {
		setJoystickValue(event.jaxis.value, &m_joystickAxisValues[whichOne].first, VECTOR_X);
	}
	// left stick move up or down
	if (event.jaxis.axis == M_LEFT_STICK_Y_AXIS) {
		setJoystickValue(event.jaxis.value, &m_joystickAxisValues[whichOne].first, VECTOR_Y);
	}
	// right stick move left or right
	if (event.jaxis.axis == M_RIGHT_STICK_X_AXIS) {
		setJoystickValue(event.jaxis.value, &m_joystickAxisValues[whichOne].second, VECTOR_X);
	}
	// right stick move up or down
	if (event.jaxis.axis == M_RIGHT_STICK_Y_AXIS) {
		setJoystickValue(event.jaxis.value, &m_joystickAxisValues[whichOne].second, VECTOR_Y);
	}
}

void InputHandler::handleButtonEvent(const SDL_Event event, const bool isDown) {
	int whichOne = event.jaxis.which;
	m_buttonStates[whichOne][event.jbutton.button] = isDown;
}

void InputHandler::setJoystickValue(const int value, Vector2D* axisVector, Vector2DCoord coord) {
	if (value > M_JOYSTICK_DEADZONE) {
		axisVector->set(coord, 1);
	}
	else if (value < -M_JOYSTICK_DEADZONE) {
		axisVector->set(coord, -1);
	}
	else {
		axisVector->set(coord, 0);
	}
}

void InputHandler::initialiseJoysticks() {
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if (SDL_NumJoysticks() == 0) {
		m_bJoysticksInitialised = false;
	}
	else {
		for (int i = 0; i < SDL_NumJoysticks(); i++) {
			SDL_Joystick* joy = SDL_JoystickOpen(i);
			if (joy) {
				m_joysticks.push_back(joy);
				// for each joystick store their stick axises values
				m_joystickAxisValues.push_back(std::make_pair(
					Vector2D(0,0),
					Vector2D(0,0)
				));
				std::vector<bool> tempButtons;
				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++) {
					tempButtons.push_back(false);
				}
				m_buttonStates.push_back(tempButtons);
			}
			else {
				std::cout << SDL_GetError();
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;
		std::cout << "Initialised "<< m_joysticks.size() << " joystick(s)\n";
	}
}

void InputHandler::clean() {
	if (m_bJoysticksInitialised) {
		for (int i = 0; i < SDL_NumJoysticks(); i++){
			SDL_JoystickClose(m_joysticks[i]);
		}
		m_joystickAxisValues.clear();

		std::cout << "Cleaned "<< m_joysticks.size() << " joystick(s)\n";
	}
}

bool InputHandler::joysticksInitialised() {
	return m_bJoysticksInitialised;
}

void InputHandler::free() {
	delete s_pInstance;
	s_pInstance = 0;
}

int InputHandler::stickXValue(const int joy, const JoystickControl stick) {
	if (m_joystickAxisValues.size() > 0) {
		if (stick == LEFT_STICK) {
			return m_joystickAxisValues[joy].first.getX();
		}
		else if (stick == RIGHT_STICK) {
			return m_joystickAxisValues[joy].second.getX();
		}
	}
	return 0;
}

int InputHandler::stickYValue(const int joy, const JoystickControl stick) {
	if (m_joystickAxisValues.size() > 0) {
		if (stick == LEFT_STICK) {
			return m_joystickAxisValues[joy].first.getY();
		}
		else if (stick == RIGHT_STICK) {
			return m_joystickAxisValues[joy].second.getY();
		}
	}
	return 0;
}
