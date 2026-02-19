#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

glm::vec2 tank_pos;
glm::vec2 tank_velocity;

Game::Game()
{
  std::cout << "Game Constructor Called\n";
  is_running = false;
}

Game::~Game()
{
  std::cout << "Game Destructor Called\n";
}

void Game::Initialize()
{
  std::cout << "Game Initializer Called\n";
  uint32_t sdl_res = SDL_Init(SDL_INIT_EVERYTHING);

  if (sdl_res != 0)
  {
    std::cerr << "Failed to Initialize SDL";
    return;
  }

  GetDisplayModeDimenesions();

  window = SDL_CreateWindow("Aye 2D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            window_width, window_height, SDL_WINDOW_BORDERLESS);

  if (!window)
  {
    std::cerr << "Error in creation of window\n";
    return;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer)
  {
    std::cerr << "Error in creation of Renderer\n";
    return;
  }

  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  is_running = true;
}

void Game::Destroy()
{
  SDL_DestroyTexture(tank_texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  std::cout << "Game Destroyer Called\n";
}

void Game::Setup()
{

  SDL_Surface* tank_surface = IMG_Load("./assets/images/tank-tiger-right.png");
  tank_texture = SDL_CreateTextureFromSurface(renderer, tank_surface);
  SDL_FreeSurface(tank_surface);

  tank_pos = glm::vec2(20, 20);
}

void Game::Run()
{
  std::cout << "Game Runner Called\n";
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

  tank_velocity = glm::vec2(0, 0);
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
      switch (sdl_event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        is_running = false;
        break;
      case SDLK_w:
        tank_velocity.y -= 5;
        break;
      case SDLK_s:
        tank_velocity.y += 5;
        break;
      case SDLK_a:
        tank_velocity.x -= 5;
        break;
      case SDLK_d:
        tank_velocity.x += 5;
        break;
      }

      break;

    default:
      break;
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
  tank_pos += tank_velocity;
}

void Game::Render()
{
  SDL_SetRenderDrawColor(renderer, 80, 80, 80, 0);
  SDL_RenderClear(renderer);

  SDL_Rect player_rect = {static_cast<int>(tank_pos.x), static_cast<int>(tank_pos.y), 32, 32};
  SDL_RenderCopy(renderer, tank_texture, NULL, &player_rect);

  SDL_RenderPresent(renderer);
}
