#include <SDL2/SDL.h>
#include <unistd.h>
#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

void parseArguments(int argc, char* args[], bool *fullScreen);

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
	Game* g;
	bool fullScreen;
	Uint32 frameStart, frameTime;

	parseArguments(argc, args, &fullScreen);

	g = Game::Instance();
	g->setUserActions();
	if (!g->init("My first window", 100, 100, 640, 480, fullScreen)) {
		return 1;
	}

	while (g->isRunning()) {
		frameStart = SDL_GetTicks();
		g->handleEvents();
		g->update();
		g->render();

		// use a delay to cap the fps
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime< DELAY_TIME) {
			SDL_Delay((int) (DELAY_TIME - frameTime));
		}
	}

	Game::freeGame();

	return 0;
}
