#include <SDL2/SDL.h>
#include <unistd.h>
#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

void parseArguments(int argc, char* args[], bool *fullScreen) {
	int c;
	while ((c = getopt (argc, args, "f")) != -1) {
		switch (c) {
			case 'f':
				*fullScreen = true;
				break;
			default:
				abort();
		}
	}
}

int main(int argc, char* args[]) {
	Game g;
	bool fullScreen;
	Uint32 frameStart, frameTime;

	parseArguments(argc, args, &fullScreen);

	if (!g.init("My first window", 100, 100, 640, 480, fullScreen)) {
		return 1;
	}

	while (g.isRunning()) {
		frameStart = SDL_GetTicks();
		g.handleEvents();
		g.update();
		g.render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime< DELAY_TIME) {
			SDL_Delay((int) (DELAY_TIME - frameTime));
		}
	}

	g.clean();

	return 0;
}
