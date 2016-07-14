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
