#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include <vector>
#include "GameStateMachine.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

class Game {
	private:
	bool m_bRunning;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	TextureManager* m_textureManager;

	GameStateMachine* m_pGameStateMachine;

	std::vector<GameObject*> m_gameObjects;
	std::vector<SDLDrawable*> m_renderableObjects;
	std::vector<Enemy*> m_enemies;
	Player* m_player;

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
	void _initActors();
	void _initGameMachine();
	void _cleanActors();
	void _cleanGameMachine();

	public:
	static Game* Instance();
	static void free();

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
};

#endif /* defined(__Game__) */
