#include <SDL2/SDL.h>
#include <unistd.h>
#include "Game.h"

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
	Game* g = new Game();
	bool fullScreen;

	parseArguments(argc, args, &fullScreen);

	if (!g->init("My first window", 100, 100, 640, 480, fullScreen)) {
		return 1;
	}

	while (g->isRunning()) {
		g->handleEvents();
		g->update();
		g->render();
	}

	g->clean();

	return 0;
}
