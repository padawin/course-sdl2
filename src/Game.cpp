#include "Game.h"
#include "Vector2D.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"
#include <iostream>
#include <errno.h>

static Game* s_pInstance;

Game::Game() {
	m_pWindow = 0;
	m_pRenderer = 0;
}

Game::~Game() {
	TextureManager::free();
	InputHandler::free();
}

Game *Game::Instance() {
	if (s_pInstance == 0) {
		s_pInstance = new Game();
	}

	return s_pInstance;
}

void Game::free() {
	delete s_pInstance;
	s_pInstance = 0;
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
	const char* fileName = "resources/char9.bmp";
	const char* errorPattern = "An error occured while loading the file %s\n%s\n";
	char errorMessage[strlen(fileName) + strlen(errorPattern) - 2];
	bool textureLoaded = m_textureManager->load(
		fileName,
		"animate",
		m_pRenderer
	);

	if (!textureLoaded) {
		sprintf(errorMessage, errorPattern, fileName, strerror(errno));
		std::cout << errorMessage;
		return false;
	}

	return true;
}

void Game::_initActors() {
	m_player = new Player();
	m_gameObjects.push_back(m_player);
	m_renderableObjects.push_back(m_player);
	m_player->load(0, 0, 128, 142);
	m_player->setTexture("animate", 6);

	int l_iNbEnemies = 4;
	for (int e = 0; e < l_iNbEnemies; ++e) {
		m_enemies.push_back(new Enemy());
		m_gameObjects.push_back(m_enemies[e]);
		m_renderableObjects.push_back(m_enemies[e]);
		m_enemies[e]->load(0, 142 * (e + 1), 128, 142);
		m_enemies[e]->setTexture("animate", 6);
	}
}

void Game::_cleanActors() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
		delete m_gameObjects[i];
		m_gameObjects[i] = NULL;
	}

	m_gameObjects.clear();
}

void Game::_initGameMachine() {
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MenuState());
}

void Game::_cleanGameMachine() {
	m_pGameStateMachine->clean();
	delete m_pGameStateMachine;
	m_pGameStateMachine = NULL;
}

bool Game::init(
	const char* title,
	const int x,
	const int y,
	const int w,
	const int h,
	const bool fullScreen
) {
	bool l_bReturn = true;
	m_textureManager = TextureManager::Instance();

	l_bReturn &= _initSDL(title, x, y, w, h, fullScreen);
	l_bReturn &= _loadResources();
	m_bRunning = l_bReturn;

	if (l_bReturn) {
		_initActors();
		InputHandler::Instance()->initialiseJoysticks();
		_initGameMachine();
	}

	return l_bReturn;
}

void Game::handleEvents() {
	bool keepRunning = InputHandler::Instance()->update();
	if (!keepRunning) {
		m_bRunning = false;
	}
	else {
		if (InputHandler::Instance()->getButtonState(0, 0)) {
			m_pGameStateMachine->changeState(new PlayState());
		}
	}
}

void Game::update() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void Game::render() {
	// set to black
	// This function expects Red, Green, Blue and
	// Alpha as color values
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	// clear the window to black
	SDL_RenderClear(m_pRenderer);

	for (std::vector<GameObject*>::size_type i = 0; i != m_renderableObjects.size(); i++) {
		m_renderableObjects[i]->render(m_pRenderer);
	}
	// show the window
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	// clean up SDL
	SDL_Quit();
	_cleanActors();
	InputHandler::Instance()->clean();
}

bool Game::isRunning() {
	return m_bRunning;
}
