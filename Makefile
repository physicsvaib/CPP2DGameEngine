CC = g++
COMPILER_FLAGS = -Wall -Wfatal-errors
LANG_STD = -std=c++17
SRC_FILES = src/*.cpp src/Game/*.cpp src/Logger/*.cpp src/ECS/*.cpp src/Systems/*.cpp src/Constants/*.cpp
INCLUDE_LIBRARIES = -lSDL2 -llua5.3 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
INCLUDE_DIRECTORIES = -I"./libs/"
DEBUG_FLAGS = -DDEBUG_SYSTEM -DDEBUG_COLLISION -DDEBUG_REGISTRY
OUTPUT = gameengine

run: 
	./$(OUTPUT)

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(SRC_FILES) $(INCLUDE_LIBRARIES) $(INCLUDE_DIRECTORIES) $(DEBUG_FLAGS) -o $(OUTPUT)

debug: build
	gdb ./$(OUTPUT)
	

clean:
	rm $(OUTPUT)