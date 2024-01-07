
all: build
build:
	mkdir -p build
# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wall -Wextra -Werror

# Library
LIBS := -lSDL2 -lm

# Source files
SRC := src/main.c src/Physics.c src/Render.c src/Vector.c

# Object files
OBJ := $(patsubst src/%.c, build/%.o, $(SRC))

# Executable name
EXEC := rigidBody

# Main target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) 

# Rule to build object files
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $< 


# Clean target
clean:
	rm -rf $(EXEC) build  

.PHONY: all clean
