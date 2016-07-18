#include "Game.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "NoJoystickState.h"
#include <iostream>
#include <errno.h>

static Game* s_pInstance;

Game::Game() {
	fileNames.push_back(std::make_pair("animate", "resources/char9.bmp"));
	fileNames.push_back(std::make_pair("mainmenu", "resources/menu-buttons.png"));
	nbFiles = 2;
}

Game::~Game() {
	InputHandler::Instance()->clean();
	InputHandler::free();
	_cleanResources();
	TextureManager::free();
	_cleanGameMachine();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
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
	m_textureManager = TextureManager::Instance();

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
		m_pWindow = SDL_CreateWindow(title, x, y, w, h, flags);
		// if the window creation succeeded create our renderer
		if (m_pWindow == 0) {
			std::cout << "Window creation failed\n";
			l_bReturn = false;
		}
		else {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer == 0) {
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
	for (int i = 0; i < nbFiles; ++i) {
		char* errorMessage = (char*) calloc(
			strlen(errorPattern) + strlen(fileNames[i].second), sizeof(char)
		);
		std::cout << "Load resource " << fileNames[i].second << "\n";
		bool textureLoaded = m_textureManager->load(
			fileNames[i].second,
			fileNames[i].first,
			m_pRenderer
		);

		if (!textureLoaded) {
			sprintf(errorMessage, errorPattern, fileNames[i].second);
			std::cout << errorMessage << "\n";
			std::cout << strerror(errno) << "\n";
			return false;
		}
		else {
			std::cout << "Resource " << fileNames[i].second << " loaded\n";
		}
		free(errorMessage);
	}

	return true;
}

void Game::_initGameMachine() {
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MenuState());
}

void Game::handleEvents() {
	bool keepRunning = InputHandler::Instance()->update();
	if (!keepRunning) {
		m_bRunning = false;
	}
}

void Game::update() {
	if (!InputHandler::Instance()->joysticksInitialised()) {
		m_pGameStateMachine->pushState(new NoJoystickState());
	}

	m_pGameStateMachine->update();
}

void Game::render() {
	// set to black
	// This function expects Red, Green, Blue and
	// Alpha as color values
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	// clear the window to black
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();
	// show the window
	SDL_RenderPresent(m_pRenderer);
}

void Game::_cleanGameMachine() {
	m_pGameStateMachine->clean();
	delete m_pGameStateMachine;
	m_pGameStateMachine = NULL;
}

void Game::_cleanResources() {
	std::cout << "Clean resources\n";
	for (int i = 0; i < nbFiles; ++i) {
		std::cout << "Clean resource " << fileNames[i].second << "\n";
		TextureManager::Instance()->clearFromTextureMap(fileNames[i].first);
	}
}

bool Game::isRunning() {
	return m_bRunning;
}

SDL_Renderer* Game::getRenderer() {
	return m_pRenderer;
}

void Game::quit() {
	m_bRunning = false;
}

GameStateMachine* Game::getStateMachine() {
	return m_pGameStateMachine;
}
