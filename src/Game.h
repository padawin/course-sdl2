#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include <vector>
#include "GameStateMachine.h"
#include "TextureManager.h"

class Game {
	private:
	/**
	 * flag to know if the game is running
	 */
	bool m_bRunning = false;

	/**
	 * The game's window
	 */
	SDL_Window* m_window = 0;

	/**
	 * The game's renderer. Used to render graphics in the window
	 */
	SDL_Renderer* m_renderer = 0;

	/**
	 * List of files to use as graphic resources, each file is a pair composed
	 * of a resource name and of the file path.
	 */
	std::vector<std::pair<const char*, const char*>> m_vResourceFiles = {};

	/**
	 * Number of resources used by the game
	 */
	int m_iNbFiles = 0;

	GameStateMachine* m_gameStateMachine = 0;

	/**
	 * The game is a singleton, so its constructor and destructor are private
	 */
	Game();
	~Game();

	/**
	 * Method to initialise the SDL. It takes in arguments the window's title,
	 * its position and dimensions, and a boolean to create it full screen or
	 * not.
	 */
	bool _initSDL(
		const char* title,
		const int x,
		const int y,
		const int w,
		const int h,
		const bool fullScreen
	);

	/**
	 * Method to load the game's resources.
	 */
	bool _loadResources();

	/**
	 * Method to free the game's resources.
	 */
	void _cleanResources();

	/**
	 * Method to initialise the state machine.
	 */
	void _initGameMachine();

	/**
	 * Method to free the state machine.
	 */
	void _cleanGameMachine();

	public:
	/**
	 * Because of the singleton, the following construct and operator are
	 * removed.
	 */
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	/**
	 * Method to get the game instance.
	 */
	static Game* Instance();

	/**
	 * Method used to clean the memory used by the game before quitting the
	 * game.
	 */
	static void freeGame();

	/**
	 * First method to be called when starting the game
	 * Initialises the game environment. It takes in arguments the
	 * window's title, its position and dimensions, and a boolean to create it
	 * full screen or not.
	 *
	 * Returns true if the game is correctly initialised.
	 */
	bool init(
		const char* title,
		const int x,
		const int y,
		const int w,
		const int h,
		bool fullScreen
	);

	/**
	 * Method called to handle the events captured by the game during each
	 * loop.
	 */
	void handleEvents();

	/**
	 * Method to update the game during each game loop.
	 */
	void update();

	/**
	 * Method to render the game during each game loop.
	 */
	void render();

	/**
	 * Method to clean the game before quitting.
	 */
	void clean();

	/**
	 * Returns true if the game is running, false otherwise.
	 */
	bool isRunning();

	/**
	 * Method to get the game's renderer. Called by any graphics having to be
	 * rendered.
	 */
	SDL_Renderer* getRenderer();

	/**
	 * Method to quit the game.
	 */
	void quit();

	/**
	 * Getter for the state machine.
	 */
	GameStateMachine* getStateMachine();
};

#endif /* defined(__Game__) */
