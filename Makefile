all:
	g++ -g -O -Wall -Weffc++ -pedantic  \
		-pedantic-errors -Wextra -Wcast-align \
		-Wcast-qual -Wconversion \
		-Wdisabled-optimization \
		-Werror -Wfloat-equal -Wformat=2 \
		-Wformat-nonliteral -Wformat-security  \
		-Wformat-y2k \
		-Wimport  -Winit-self  -Winline \
		-Winvalid-pch   \
		-Wlong-long \
		-Wmissing-field-initializers -Wmissing-format-attribute   \
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
	src/*.cpp -lSDL2 -lSDL2_image -o sdl-example
