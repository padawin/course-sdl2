all:
	g++ -Wall src/main.cpp src/Game.cpp src/TextureManager.cpp -lSDL2 -lSDL2_image -o sdl-example
