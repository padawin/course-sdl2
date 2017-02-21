#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include "SDL2_framework/Game.h"
#include "SDL2_framework/GameObjectFactory.h"
#include "SDL2_framework/MenuButton.h"
#include "Player.h"
#include "Enemy.h"
#include "MainMenuState.h"
#include <libgen.h>
#include <iostream>

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

void parseArguments(int argc, char* args[], bool *fullScreen);
void initResources(std::string binaryPath, Game* game);
void initObjectTypes();

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
	char buffer[1024];
	std::string binaryPath;
	Uint32 frameStart, frameTime;

	parseArguments(argc, args, &fullScreen);

	realpath(dirname(args[0]), buffer);
	binaryPath = buffer;
	g = Game::Instance();
	initResources(binaryPath, g);
	initObjectTypes();
	g->setBinaryPath(binaryPath);
	if (!g->init("My first window", 100, 100, 640, 480, fullScreen)) {
		Game::freeGame();
		return 1;
	}

	g->getStateMachine()->changeState(new MainMenuState());
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

void initResources(std::string binaryPath, Game* game) {
	std::string menuButtons = binaryPath + "/../resources/menu-buttons.png";
	std::string pauseMenuButtons = binaryPath + "/../resources/pause-menu-buttons.png";
	game->addResource("mainmenu", menuButtons);
	game->addResource("pausemenu", pauseMenuButtons);
}

void initObjectTypes() {
	// object types
	GameObjectFactory::Instance()->registerType(
	   "MenuButton", new MenuButtonCreator()
	);
	GameObjectFactory::Instance()->registerType(
	   "Player", new PlayerCreator()
	);
	GameObjectFactory::Instance()->registerType(
	   "Enemy", new EnemyCreator()
	);
}
