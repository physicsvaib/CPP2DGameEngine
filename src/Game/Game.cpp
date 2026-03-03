#include "Game.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

Game::Game()
{
    Logger::Info("Game Constructor Called");
    is_running = false;
    registry = std::make_unique<Registry>();
}

Game::~Game()
{
    Logger::Info("Game Destructor Called");
}

void Game::Initialize()
{
    Logger::Info("Game Initializer Called");
    uint32_t sdl_res = SDL_Init(SDL_INIT_EVERYTHING);

    if (sdl_res != 0)
    {
        Logger::Error("Failed to Initialize SDL");
        return;
    }

    GetDisplayModeDimenesions();

    window = SDL_CreateWindow("Aye 2D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              window_width, window_height, SDL_WINDOW_BORDERLESS);

    if (!window)
    {
        Logger::Error("Error in creation of window");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        Logger::Error("Error in creation of Renderer");
        return;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    is_running = true;
}

void Game::Destroy()
{
    // SDL_DestroyTexture(tank_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    Logger::Info("Game Destroyer Called");
}

void Game::Setup()
{

    Entity tank = registry->CreateEntity();
    registry->AddComponent<TransformComponent>(tank, glm::vec2(11.0, 33.0), glm::vec2(1.0, 1.0),
                                               0.0);
    registry->AddComponent<RigidbodyComponent>(tank, glm::vec2(50.0, 0.0));

    // TODO:
    // Entity tank = registry.CreateEntity();
    // tank.AddComponent<TransformComponent>();
    // tank.AddComponent<BoxCollisionComponent>();
    // tank.AddComponent<SpriteComponent>(SpriteReferences.TANK_FILE);
}

void Game::Run()
{
    Logger::Info("Game Runner Called");
    Setup();

    while (is_running)
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::ProcessInput()
{
    KeyBoardInput();
}

void Game::KeyBoardInput()
{
    // Make a better method on this
    SDL_Event sdl_event;

    // using a while loop for getting over multiple events
    // ghosting is the best case i feel
    // ok i checked not ghosting, its the queue of inputs that build up
    // that we for sure should empty before completing things and going next frame
    while (SDL_PollEvent(&sdl_event))
    {
        switch (sdl_event.type)
        {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (sdl_event.key.keysym.sym == SDLK_ESCAPE)
            {
                is_running = false;
            }
        }
    }
}

void Game::GetDisplayModeDimenesions()
{
    SDL_DisplayMode display_mode;

    // Hard coded 0
    SDL_GetCurrentDisplayMode(0, &display_mode);

    window_width = display_mode.w;
    window_height = display_mode.h;
}

void Game::Update()
{
    TimeLogic();

    // TODO: MovementSystem.Update()
}

void Game::TimeLogic()
{
    int start_time = SDL_GetTicks();
    int delta = start_time - ms_passed;
    int time_to_delay = MILLISECONDS_PER_FRAME - delta;

    if (CAP_FPS)
    {
        if (time_to_delay <= MILLISECONDS_PER_FRAME && time_to_delay > 0)
        {
            SDL_Delay(time_to_delay);
        }
    }

    delta_time = delta / 1000.0;
    ms_passed = start_time;
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 0);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}
