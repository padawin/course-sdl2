#include "Game.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "NoJoystickState.h"
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "Player.h"
#include "Enemy.h"
#include "UserActions.h"
#include "ServiceProvider.h"
#include <iostream>
#include <errno.h>

static Game* s_pInstance;

/**
 * Game construct, Initialises the vector of resource names.
 */
Game::Game() {
	m_vResourceFiles.push_back(std::make_pair("animate", "resources/char9.png"));
	m_vResourceFiles.push_back(std::make_pair("mainmenu", "resources/menu-buttons.png"));
	m_vResourceFiles.push_back(std::make_pair("pausemenu", "resources/pause-menu-buttons.png"));
	m_iNbFiles = (int) m_vResourceFiles.size();

	// object types
	GameObjectFactory::Instance()->registerType(
		"MenuButton", new MenuButtonCreator()
	);
	GameObjectFactory::Instance()->registerType(
		"Player", new PlayerCreator()
	);
	GameObjectFactory::Instance()->registerType(
		"Enemy", new EnemyCreator()
	);
}

/**
 * Game destructor, cleans the InputHandler, the resources, the state machine
 * and stops the SDL.
 */
Game::~Game() {
	InputHandler::Instance()->clean();
	InputHandler::free();
	GameObjectFactory::free();
	_cleanResources();
	TextureManager::free();
	_cleanGameMachine();
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

/**
 * Classic singleton method to get the Game instance.
 */
Game *Game::Instance() {
	if (s_pInstance == 0) {
		s_pInstance = new Game();
	}

	return s_pInstance;
}

/**
 * Deletes the game instance.
 */
void Game::freeGame() {
	delete s_pInstance;
	s_pInstance = 0;
}

/**
 * Initialises the SDL, loads the resources and initialises the State machine.
 * Then sets te m_bRunning flag to true.
 */
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
		m_iScreenWidth = w;
		m_iScreenHeight = h;
		_initGameMachine();
		_initServiceProvider();
		l_bReturn = true;
		m_bRunning = true;
	}

	return l_bReturn;
}

/**
 * Classic SDL initialisation.
 */
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

/**
 * Loads each resource. Returns false if a resource is failed to be loaded (for
 * example if the file does not exist or is not readable).
 */
bool Game::_loadResources() {
	const char errorPattern[] = "An error occured while loading the file %s";

	std::cout << "Load resources \n";
	for (int i = 0; i < m_iNbFiles; ++i) {
		char* errorMessage = (char*) calloc(
			strlen(errorPattern) + strlen(m_vResourceFiles[i].second), sizeof(char)
		);
		std::cout << "Load resource " << m_vResourceFiles[i].second << "\n";
		bool textureLoaded = TextureManager::Instance()->load(
			m_vResourceFiles[i].second,
			m_vResourceFiles[i].first,
			m_renderer
		);

		if (!textureLoaded) {
			sprintf(errorMessage, errorPattern, m_vResourceFiles[i].second);
			std::cout << errorMessage << "\n";
			std::cout << strerror(errno) << "\n";
			return false;
		}
		else {
			std::cout << "Resource " << m_vResourceFiles[i].second << " loaded\n";
		}
		free(errorMessage);
	}

	return true;
}

/**
 * Initialises the State machine and sets the MainMenu state as initial state.
 */
void Game::_initGameMachine() {
	m_gameStateMachine = new GameStateMachine();
	m_gameStateMachine->changeState(new MainMenuState());
}

/**
 * Update the input handler, if the update returns false, the game stops
 * running.
 */
void Game::handleEvents() {
	bool keepRunning = InputHandler::Instance()->update();
	if (!keepRunning) {
		m_bRunning = false;
	}
}

/**
 * Method to be called at each game loop, if no joystick is detected, the state
 * NoJoystickState is pushed, until a joystick is plugged.
 * The state machines updates its current state.
 */
void Game::update() {
	if (!InputHandler::Instance()->joysticksInitialised()) {
		m_gameStateMachine->pushState(new NoJoystickState());
	}

	m_gameStateMachine->update();
}

/**
 * Method to be called at each game loop. Renders the current state.
 */
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

/**
 * Clean every resources.
 */
void Game::_cleanResources() {
	std::cout << "Clean resources\n";
	for (int i = 0; i < m_iNbFiles; ++i) {
		std::cout << "Clean resource " << m_vResourceFiles[i].second << "\n";
		TextureManager::Instance()->clearFromTextureMap(m_vResourceFiles[i].first);
	}
}

bool Game::isRunning() {
	return m_bRunning;
}

SDL_Renderer* Game::getRenderer() {
	return m_renderer;
}

/**
 * Set running to false, which then will stop the game loop.
 */
void Game::quit() {
	m_bRunning = false;
}

GameStateMachine* Game::getStateMachine() {
	return m_gameStateMachine;
}

int Game::getScreenWidth() {
	return m_iScreenWidth;
}

int Game::getScreenHeight() {
	return m_iScreenHeight;
}

void Game::_initServiceProvider() {
	UserActions* userActions = new UserActions();
	Command pauseJoystick;
	pauseJoystick.type = CONTROLLER_BUTTON;
	pauseJoystick.buttonId = 7;
	userActions->add("PAUSE", pauseJoystick);
	Command pauseKeyboard;
	pauseKeyboard.type = KEYBOARD_KEY;
	pauseKeyboard.key = SDL_SCANCODE_ESCAPE;
	userActions->add("PAUSE", pauseKeyboard);

	Command menuNextJoystick;
	menuNextJoystick.type = CONTROLLER_STICK;
	menuNextJoystick.stickAxis = LEFT_STICK_Y;
	menuNextJoystick.stickDirection = 1;
	userActions->add("CHANGE_MENU_NEXT", menuNextJoystick);

	Command menuPreviousJoystick;
	menuPreviousJoystick.type = CONTROLLER_STICK;
	menuPreviousJoystick.stickAxis = LEFT_STICK_Y;
	menuPreviousJoystick.stickDirection = -1;
	userActions->add("CHANGE_MENU_PREVIOUS", menuPreviousJoystick);

	Command activateMenuButtonJoystick;
	activateMenuButtonJoystick.type = CONTROLLER_BUTTON;
	activateMenuButtonJoystick.buttonId = 0;
	userActions->add("ACTIVATE_MENU_BUTTON", activateMenuButtonJoystick);
	Command activateMenuButtonKeyboard;
	activateMenuButtonKeyboard.type = KEYBOARD_KEY;
	activateMenuButtonKeyboard.key = SDL_SCANCODE_RETURN;
	userActions->add("ACTIVATE_MENU_BUTTON", activateMenuButtonKeyboard);

	Command playerRushJoystick;
	playerRushJoystick.type = CONTROLLER_BUTTON;
	playerRushJoystick.buttonId = 1;
	userActions->add("PLAYER_RUSH", playerRushJoystick);

	ServiceProvider::setUserActions(userActions);
}
