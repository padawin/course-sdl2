#include <SDL2/SDL.h>
#include "Game.h"

int main(int argc, char* args[]) {
	Game* g = new Game();

	if (!g->init("My first window", 100, 100, 640, 480, true)) {
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
