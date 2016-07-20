#include "Game.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "NoJoystickState.h"
#include <iostream>
#include <errno.h>

static Game* s_pInstance;

Game::Game() {
	m_vFileNames.push_back(std::make_pair("animate", "resources/char9.bmp"));
	m_vFileNames.push_back(std::make_pair("mainmenu", "resources/menu-buttons.png"));
	m_vFileNames.push_back(std::make_pair("pausemenu", "resources/pause-menu-buttons.png"));
	m_iNbFiles = (int) m_vFileNames.size();
}

Game::~Game() {
	InputHandler::Instance()->clean();
	InputHandler::free();
	_cleanResources();
	TextureManager::free();
	_cleanGameMachine();
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	// clean up SDL
	SDL_Quit();
}

Game *Game::Instance() {
	if (s_pInstance == 0) {
		s_pInstance = new Game();
	}

	return s_pInstance;
}

void Game::freeGame() {
	delete s_pInstance;
	s_pInstance = 0;
}

bool Game::init(
	const char* title,
	const int x,
	const int y,
	const int w,
	const int h,
	const bool fullScreen
) {
	bool l_bReturn = false;
	if (_initSDL(title, x, y, w, h, fullScreen) && _loadResources()) {
		_initGameMachine();
		l_bReturn = true;
		m_bRunning = true;
	}

	return l_bReturn;
}

bool Game::_initSDL(
	const char* title,
	const int x,
	const int y,
	const int w,
	const int h,
	const bool fullScreen
) {
	bool l_bReturn = true;
	int flags = 0;

	if (fullScreen) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL Init failed\n";
		l_bReturn = false;
	}
	else {
		// if succeeded create our window
		m_window = SDL_CreateWindow(title, x, y, w, h, flags);
		// if the window creation succeeded create our renderer
		if (m_window == 0) {
			std::cout << "Window creation failed\n";
			l_bReturn = false;
		}
		else {
			m_renderer = SDL_CreateRenderer(m_window, -1, 0);
			if (m_renderer == 0) {
				std::cout << "Renderer creation failed\n";
				l_bReturn = false;
			}
		}
	}

	return l_bReturn;
}

bool Game::_loadResources() {
	const char errorPattern[] = "An error occured while loading the file %s";

	std::cout << "Load resources \n";
	for (int i = 0; i < m_iNbFiles; ++i) {
		char* errorMessage = (char*) calloc(
			strlen(errorPattern) + strlen(m_vFileNames[i].second), sizeof(char)
		);
		std::cout << "Load resource " << m_vFileNames[i].second << "\n";
		bool textureLoaded = TextureManager::Instance()->load(
			m_vFileNames[i].second,
			m_vFileNames[i].first,
			m_renderer
		);

		if (!textureLoaded) {
			sprintf(errorMessage, errorPattern, m_vFileNames[i].second);
			std::cout << errorMessage << "\n";
			std::cout << strerror(errno) << "\n";
			return false;
		}
		else {
			std::cout << "Resource " << m_vFileNames[i].second << " loaded\n";
		}
		free(errorMessage);
	}

	return true;
}

void Game::_initGameMachine() {
	m_gameStateMachine = new GameStateMachine();
	m_gameStateMachine->changeState(new MainMenuState());
}

void Game::handleEvents() {
	bool keepRunning = InputHandler::Instance()->update();
	if (!keepRunning) {
		m_bRunning = false;
	}
}

void Game::update() {
	if (!InputHandler::Instance()->joysticksInitialised()) {
		m_gameStateMachine->pushState(new NoJoystickState());
	}

	m_gameStateMachine->update();
}

void Game::render() {
	// set to black
	// This function expects Red, Green, Blue and
	// Alpha as color values
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	// clear the window to black
	SDL_RenderClear(m_renderer);

	m_gameStateMachine->render();
	// show the window
	SDL_RenderPresent(m_renderer);
}

void Game::_cleanGameMachine() {
	m_gameStateMachine->clean();
	delete m_gameStateMachine;
	m_gameStateMachine = NULL;
}

void Game::_cleanResources() {
	std::cout << "Clean resources\n";
	for (int i = 0; i < m_iNbFiles; ++i) {
		std::cout << "Clean resource " << m_vFileNames[i].second << "\n";
		TextureManager::Instance()->clearFromTextureMap(m_vFileNames[i].first);
	}
}

bool Game::isRunning() {
	return m_bRunning;
}

SDL_Renderer* Game::getRenderer() {
	return m_renderer;
}

void Game::quit() {
	m_bRunning = false;
}

GameStateMachine* Game::getStateMachine() {
	return m_gameStateMachine;
}
