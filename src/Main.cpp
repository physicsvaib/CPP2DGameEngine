#include <iostream>
#include "sol/sol.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "glm/glm.hpp"
#include "imgui/imgui.h"

int main()
{
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    SDL_Init(SDL_INIT_EVERYTHING);
    std::cout << "Hello, Gabe!" << std::endl;
    return 0;
}
