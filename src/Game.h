#include <SDL2/SDL.h>

class Game {
	private:
	bool m_bRunning;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

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
