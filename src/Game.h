#ifndef GAME_H
#define GAME_H

const int FPS = 3;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;
const bool CAP_FPS = false;

class Game
{
private:
  struct SDL_Window* window;
  struct SDL_Renderer* renderer;
  void KeyBoardInput();
  void GetDisplayModeDimenesions();

  bool is_running;
  struct SDL_Texture* tank_texture;
  double delta_time = 0;

  int window_width;
  int window_height;

  int ms_passed = 0;

public:
  Game();
  ~Game();

  void Initialize();
  void Destroy();
  void Setup();

  void Run();

  void ProcessInput();
  void Update();
  void Render();
};

#endif