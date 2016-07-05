#include "Game.h"
#include <iostream>

Game::Game() {
	m_pWindow = 0;
	m_pRenderer = 0;
}

Game::~Game() {

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
	m_textureManager.load("resources/char9.bmp", "animate", m_pRenderer);
	return true;
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

	l_bReturn &= _initSDL(title, x, y, w, h, fullScreen);
	l_bReturn &= _loadResources();
	m_bRunning = l_bReturn;
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
}

void Game::render() {
	// set to black
	// This function expects Red, Green, Blue and
	// Alpha as color values
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	// clear the window to black
	SDL_RenderClear(m_pRenderer);
	m_textureManager.draw(
		"animate",
		0, 0, 128, 142,
		m_pRenderer
	);
	// show the window
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	// clean up SDL
	SDL_Quit();
}

bool Game::isRunning() {
	return m_bRunning;
}
