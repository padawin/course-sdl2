#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include "TextureManager.h"

class Game {
	private:
	bool m_bRunning;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	TextureManager m_textureManager;

	bool _initSDL(
		const char* title,
		const int x,
		const int y,
		const int w,
		const int h,
		const bool fullScreen
	);
	bool _loadResources();

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
