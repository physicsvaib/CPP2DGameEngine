CC = g++
COMPILER_FLAGS = -Wall -Wfatal-errors
LANG_STD = -std=c++17
SRC_FILES = src/*.cpp src/Game/*.cpp src/Logger/*.cpp
INCLUDE_LIBRARIES = -lSDL2 -llua5.3 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
INCLUDE_DIRECTORIES = -I"./libs/"
OUTPUT = gameengine

run: 
	./$(OUTPUT)

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(SRC_FILES) $(INCLUDE_LIBRARIES) $(INCLUDE_DIRECTORIES) -o $(OUTPUT)

clean:
	rm $(OUTPUT)