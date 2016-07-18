#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include <vector>
#include "GameStateMachine.h"
#include "TextureManager.h"

class Game {
	private:
	bool m_bRunning = false;
	SDL_Window* m_pWindow = 0;
	SDL_Renderer* m_pRenderer = 0;
	TextureManager* m_textureManager = 0;

	std::vector<std::pair<const char*, const char*>> fileNames = {};
	int nbFiles = 0;

	GameStateMachine* m_pGameStateMachine = 0;

	Game();
	~Game();

	bool _initSDL(
		const char* title,
		const int x,
		const int y,
		const int w,
		const int h,
		const bool fullScreen
	);
	bool _loadResources();
	void _cleanResources();
	void _initGameMachine();
	void _cleanGameMachine();

	public:
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
	static Game* Instance();
	static void freeGame();

	bool init(
		const char* title,
		const int x,
		const int y,
		const int w,
		const int h,
		bool fullScreen
	);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool isRunning();
	SDL_Renderer* getRenderer();

	void quit();
	GameStateMachine* getStateMachine();
};

#endif /* defined(__Game__) */
