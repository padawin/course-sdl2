# A random game with the SDL2

## Dependencies

g++
libsdl2-dev
libsdl2-image-dev
libconfig++-dev

To regenerate the configure and Makefile:

	libtoolize
	aclocal
	autoconf
	automake -a

## Compilation

	./configure
	make
	make install

## Usage

Just run:

	./bin/sdl-example
