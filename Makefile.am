AUTOMAKE_OPTIONS = gnu

libSDL_framework_la_CXXFLAGS=-std=c++11 -O2 -Wmissing-declarations -Weffc++ \
		-Wall -I/usr/local/include \
		-pedantic -pedantic-errors -Wextra -Wcast-align \
		-Wcast-qual -Wconversion \
		-Wdisabled-optimization \
		-Werror -Wfloat-equal -Wformat=2 \
		-Wformat-nonliteral -Wformat-security \
		-Wformat-y2k \
		-Wimport -Winit-self -Winline \
		-Winvalid-pch \
		-Wlong-long \
		-Wmissing-field-initializers -Wmissing-format-attribute \
		-Wmissing-include-dirs -Wmissing-noreturn \
		-Wpacked -Wpointer-arith \
		-Wredundant-decls \
		-Wshadow -Wstack-protector \
		-Wstrict-aliasing=2 -Wswitch-default \
		-Wswitch-enum \
		-Wunreachable-code -Wunused \
		-Wunused-parameter \
		-Wvariadic-macros \
		-Wwrite-strings \
		-DVERSION=\"$(VERSION)\" -DPROG="\"$(PACKAGE)\""
AM_LDFLAGS=-L/usr/local/lib -lSDL2 -lSDL2_image -ltinyxml -lz

otherincludedir = $(includedir)/SDL_framework
otherinclude_HEADERS = src/Game.h src/GameObject.h src/GameObjectCollection.h src/GameObjectCreator.h src/GameObjectFactory.h src/GameState.h src/GameStateMachine.h src/GameStateParser.h src/InputHandler.h src/Layer.h src/Level.h src/LevelParser.h src/MenuButton.h src/MenuState.h src/NoJoystickState.h src/ObjectLayer.h src/SDLDrawable.h src/ServiceProvider.h src/TextureManager.h src/TileLayer.h src/UserActions.h src/Vector2D.h src/base64.h src/objectParser.h

lib_LTLIBRARIES = libSDL_framework.la
libSDL_framework_la_SOURCES=src/Game.cpp src/GameObjectCollection.cpp src/GameObjectFactory.cpp src/GameState.cpp src/GameStateMachine.cpp src/GameStateParser.cpp src/InputHandler.cpp src/Level.cpp src/LevelParser.cpp src/MenuButton.cpp src/MenuState.cpp src/NoJoystickState.cpp src/ObjectLayer.cpp src/objectParser.cpp src/SDLDrawable.cpp src/ServiceProvider.cpp src/TextureManager.cpp src/TileLayer.cpp src/tinystr.cpp src/tinyxml.cpp src/tinyxmlparser.cpp src/UserActions.cpp src/Vector2D.cpp

libSDL_framework_la_LIBADD = libbase64.a
noinst_LIBRARIES = libbase64.a
libbase64_a_SOURCES = src/base64.cpp
libbase64_a_CXXFLAGS = $(CXXFLAGS)
