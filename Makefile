run: build
	./gameengine

build:
	g++ -Wall -std=c++17 src/*.cpp -I"./libs/" -lSDL2 -llua5.3 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o gameengine

clean:
	rm gameengine