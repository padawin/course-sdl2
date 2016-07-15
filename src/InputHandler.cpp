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
			int whichOne = event.jaxis.which;
			std::cout << "Joystick " << whichOne << " manipulated\n";
		}
	}

	return ret;
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

int InputHandler::xValue(int joy, int stick) {
	if (m_joystickAxisValues.size() > 0) {
		if (stick == 1) {
			return m_joystickAxisValues[joy].first.getX();
		}
		else if (stick == 2) {
			return m_joystickAxisValues[joy].second.getX();
		}
	}
	return 0;
}

int InputHandler::yValue(int joy, int stick) {
	if (m_joystickAxisValues.size() > 0) {
		if (stick == 1) {
			return m_joystickAxisValues[joy].first.getY();
		}
		else if (stick == 2) {
			return m_joystickAxisValues[joy].second.getY();
		}
	}
	return 0;
}
