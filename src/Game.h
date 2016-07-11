#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include <vector>
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

	std::vector<GameObject*> m_gameObjects;
	std::vector<SDLDrawable*> m_renderableObjects;
	std::vector<Enemy*> m_enemies;
	Player* m_player;

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
	void _cleanActors();

	public:
	Game();
	~Game();

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
};

#endif /* defined(__Game__) */
