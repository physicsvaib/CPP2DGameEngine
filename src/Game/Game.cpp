#include "Game.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Logger/Logger.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

Game::Game()
{
    Logger::Log("Game Constructor Called");
    is_running = false;
    registry = std::make_unique<Registry>();
    assetStore = std::make_unique<AssetStore>();
}

Game::~Game()
{
    Logger::Log("Game Destructor Called");
}

void Game::Initialize()
{
    Logger::Log("Game Initializer Called");
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
    Logger::Log("Game Destroyer Called");
}

void Game::Setup()
{

    Entity tank = registry->CreateEntity();
    Entity truck = registry->CreateEntity();

    assetStore->AddTexture(renderer, PhywSprite::TANK_PANTHER_RIGHT, "tank-panther-right.png");
    assetStore->AddTexture(renderer, PhywSprite::TRUCK_FORD_RIGHT, "truck-ford-down.png");

    tank.AddComponent<TransformComponent>(glm::vec2(30.0, 10.0), glm::vec2(1.0, 1.0), 0.0);
    tank.AddComponent<RigidbodyComponent>(glm::vec2(50.0, 0.0));
    tank.AddComponent<SpriteComponent>(PhywSprite::TANK_PANTHER_RIGHT, 100, 100);

    truck.AddComponent<TransformComponent>(glm::vec2(8.0, 20.0), glm::vec2(1.0, 1.0), 0.0);
    truck.AddComponent<RigidbodyComponent>(glm::vec2(0.0, 50.0));
    truck.AddComponent<SpriteComponent>(PhywSprite::TRUCK_FORD_RIGHT, 30, 30);

    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();
}

void Game::Run()
{
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
    registry->GetSystem<MovementSystem>().Update(deltaTime);

    registry->Update();

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

    deltaTime = delta / 1000.0;
    ms_passed = start_time;
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 0);
    SDL_RenderClear(renderer);
    registry->GetSystem<RenderSystem>().Update(renderer, assetStore);

    SDL_RenderPresent(renderer);
}
