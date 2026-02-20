#include "Game.h"
#include "Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

glm::vec2 tank_pos;
glm::vec2 tank_velocity;

Game::Game()
{
  Logger::Info("Game Constructor Called");
  is_running = false;
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
  SDL_DestroyTexture(tank_texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  Logger::Info("Game Destroyer Called");
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
      if (sdl_event.key.keysym.sym == SDLK_ESCAPE)
      {
        is_running = false;
      }
      if (sdl_event.key.keysym.sym == SDLK_w)
      {
        tank_velocity.y -= 5;
      }
      if (sdl_event.key.keysym.sym == SDLK_s)
      {
        tank_velocity.y += 5;
      }
      if (sdl_event.key.keysym.sym == SDLK_d)
      {
        tank_velocity.x += 5;
      }
      if (sdl_event.key.keysym.sym == SDLK_a)
      {
        tank_velocity.x -= 5;
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
  // while (!SDL_TICKS_PASSED(SDL_GetTicks(), ms_passed + MILLISECONDS_PER_FRAME));

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

  tank_pos.x += 1000 * delta_time;
  tank_pos.y += tank_velocity.y * delta_time;
}

void Game::Render()
{
  SDL_SetRenderDrawColor(renderer, 80, 80, 80, 0);
  SDL_RenderClear(renderer);

  SDL_Rect player_rect = {static_cast<int>(tank_pos.x), static_cast<int>(tank_pos.y), 32, 32};
  SDL_RenderCopy(renderer, tank_texture, NULL, &player_rect);

  SDL_RenderPresent(renderer);
}
