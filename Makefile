BINDIR := bin
SRCDIR := src
BUILDDIR := build

PROG   := sdl-example
CC     := g++
INCL   :=
CFLAGS := -g -O2 -Wall -Wmissing-declarations -Weffc++ \
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
		-Wwrite-strings
LDFLAGS:= -I./$(SRCDIR)
CCDYNAMICFLAGS := ${CFLAGS} ${LDFLAGS} -Ivendor/ -lSDL2 -lSDL2_image -ltinyxml -lz

SRC := $(shell find $(SRCDIR)/ -type f -name '*.cpp')
OBJ := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRC))
DEP := $(patsubst %.o,%.deps,$(OBJ))

all: $(PROG)

-include $(DEP)

%.deps: %.cpp
	$(CC) -MM $< >$@

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) -c -MMD $(patsubst $(BUILDDIR)/%.o,%.cpp,$@) -o $@

clean:
	rm -rf $(BINDIR) $(BUILDDIR)

$(PROG): $(OBJ)
	mkdir -p $(BINDIR)
	$(CC) -o $(BINDIR)/$@ $^ $(CCDYNAMICFLAGS)
