#include "InputHandler.h"
#include <iostream>
#include <SDL2/SDL.h>

static InputHandler* s_pInstance;

InputHandler::InputHandler() {
	m_bJoysticksInitialised = false;
	SDL_JoystickEventState(SDL_ENABLE);
}

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
		else if (event.type == SDL_JOYDEVICEADDED) {
			initialiseJoystick(event.cdevice.which);
		}
		else if (event.type == SDL_JOYDEVICEREMOVED) {
			handleJoystickRemoved(event);
		}
	}

	return ret;
}

void InputHandler::handleStickEvent(const SDL_Event event) {
	int joystickId = event.jaxis.which;
	// left stick move left or right
	if (event.jaxis.axis == M_LEFT_STICK_X_AXIS) {
		setJoystickValue(event.jaxis.value, &m_joystickAxisValues[joystickId].first, VECTOR_X);
	}
	// left stick move up or down
	if (event.jaxis.axis == M_LEFT_STICK_Y_AXIS) {
		setJoystickValue(event.jaxis.value, &m_joystickAxisValues[joystickId].first, VECTOR_Y);
	}
	// right stick move left or right
	if (event.jaxis.axis == M_RIGHT_STICK_X_AXIS) {
		setJoystickValue(event.jaxis.value, &m_joystickAxisValues[joystickId].second, VECTOR_X);
	}
	// right stick move up or down
	if (event.jaxis.axis == M_RIGHT_STICK_Y_AXIS) {
		setJoystickValue(event.jaxis.value, &m_joystickAxisValues[joystickId].second, VECTOR_Y);
	}
}

void InputHandler::handleButtonEvent(const SDL_Event event, const bool isDown) {
	int joystickId = event.jaxis.which;
	m_buttonStates[joystickId][event.jbutton.button] = isDown;
}

void InputHandler::handleJoystickRemoved(const SDL_Event event) {
	clean();
}

void InputHandler::setJoystickValue(const int value, Vector2D* axisVector, Vector2DCoord coord) {
	if (value > M_JOYSTICK_DEADZONE) {
		axisVector->set(coord, 1.0);
	}
	else if (value < -M_JOYSTICK_DEADZONE) {
		axisVector->set(coord, -1.0);
	}
	else {
		axisVector->set(coord, 0.0);
	}
}

void InputHandler::initialiseJoystick(const int indexJoystick) {
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	SDL_Joystick* joy = SDL_JoystickOpen(indexJoystick);
	if (!joy) {
		std::cout << SDL_GetError();
	}
	else {
		int joystickId = SDL_JoystickInstanceID(joy);
		m_joysticks.push_back(std::make_pair(joystickId, joy));
		// for each joystick store their stick axises values
		m_joystickAxisValues[joystickId] = std::make_pair(
			Vector2D(0,0),
			Vector2D(0,0)
		);
		std::vector<bool> tempButtons;
		for (int j = 0; j < SDL_JoystickNumButtons(joy); j++) {
			tempButtons.push_back(false);
		}
		m_buttonStates[joystickId] = tempButtons;
		m_bJoysticksInitialised = true;
		std::cout << "Initialised "<< m_joysticks.size() << " joystick(s)\n";
	}
}

void InputHandler::clean() {
	if (m_bJoysticksInitialised) {
		int nbJoysticks = (int) m_joysticks.size();
		for (int i = 0; i < nbJoysticks; i++){
			SDL_JoystickClose(m_joysticks[i].second);
			m_joysticks[i].second = NULL;
		}

		std::cout << "Cleaned "<< m_joysticks.size() << " joystick(s)\n";
		m_joysticks.clear();
		m_buttonStates.clear();
		m_joystickAxisValues.clear();

		m_bJoysticksInitialised = false;
	}
}

bool InputHandler::joysticksInitialised() {
	return m_bJoysticksInitialised;
}

void InputHandler::free() {
	delete s_pInstance;
	s_pInstance = 0;
}

int InputHandler::stickXValue(const int joyIndex, const JoystickControl stick) {
	if (m_joystickAxisValues.size() > 0) {
		if (stick == LEFT_STICK) {
			return (int) m_joystickAxisValues[m_joysticks[joyIndex].first].first.getX();
		}
		else if (stick == RIGHT_STICK) {
			return (int) m_joystickAxisValues[m_joysticks[joyIndex].first].second.getX();
		}
	}
	return 0;
}

int InputHandler::stickYValue(const int joyIndex, const JoystickControl stick) {
	if (m_joystickAxisValues.size() > 0) {
		if (stick == LEFT_STICK) {
			return (int) m_joystickAxisValues[m_joysticks[joyIndex].first].first.getY();
		}
		else if (stick == RIGHT_STICK) {
			return (int) m_joystickAxisValues[m_joysticks[joyIndex].first].second.getY();
		}
	}
	return 0;
}

bool InputHandler::getButtonState(int joyIndex, int buttonNumber) {
	return m_buttonStates[m_joysticks[joyIndex].first][buttonNumber];
}
