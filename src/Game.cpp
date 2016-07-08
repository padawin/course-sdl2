#include "Game.h"
#include <iostream>
#include <errno.h>

Game::Game() {
	m_pWindow = 0;
	m_pRenderer = 0;
}

Game::~Game() {
	TextureManager::free();
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
	m_player->load(0, 0, 128, 142);
	m_player->setTexture("animate", 6);
}

void Game::_cleanActors() {
	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
		delete m_gameObjects[i];
	}

	m_gameObjects.clear();
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
	}

	return l_bReturn;
}

void Game::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_bRunning = false;
				break;
			default:
				break;
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

	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
		m_gameObjects[i]->render(m_pRenderer);
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
}

bool Game::isRunning() {
	return m_bRunning;
}
