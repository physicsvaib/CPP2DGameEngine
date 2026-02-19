#ifndef GAME_H
#define GAME_H

const int FPS = 30;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;

class Game
{
private:
  struct SDL_Window* window;
  struct SDL_Renderer* renderer;
  void KeyBoardInput();
  void GetDisplayModeDimenesions();

  bool is_running;
  struct SDL_Texture* tank_texture;

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

  int window_width;
  int window_height;
};

#endif