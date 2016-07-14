#include "InputHandler.h"

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

void InputHandler::free() {
	delete s_pInstance;
	s_pInstance = 0;
}
