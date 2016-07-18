#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState *pState) {
	// if the current state is the same as the pushed one, do nothing
	if (!m_gameStates.empty() && m_gameStates.back()->getStateID() == pState->getStateID()) {
		return;
	}

	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState *pState) {
	// If there is at least one state
	if (!m_gameStates.empty()) {
		// and if it is the state we want to add
		if (m_gameStates.back()->getStateID() == pState->getStateID()) {
			return;
		}

		// remove the state
		popState();
	}

	// add the new one
	pushState(pState);
}

bool GameStateMachine::popState() {
	if (!m_gameStates.empty() && m_gameStates.back()->onExit()) {
		delete m_gameStates.back();
		m_gameStates.pop_back();
		return true;
	}

	return false;
}

void GameStateMachine::clean() {
	while (popState()) {}
}

GameState* GameStateMachine::getCurrentState() {
	return m_gameStates.back();
}

void GameStateMachine::update() {
	if (!m_gameStates.empty()) {
		m_gameStates.back()->update();
	}
}
void GameStateMachine::render() {
	if (!m_gameStates.empty()) {
		m_gameStates.back()->render();
	}
}
