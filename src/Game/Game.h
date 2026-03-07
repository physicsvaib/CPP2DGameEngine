#ifndef GAME_H
#define GAME_H

#include "../Constants/AssetStore.h"
#include "../ECS/Registry.h"

const int FPS = 3;
const int MILLISECONDS_PER_FRAME = 1000 / FPS;
const bool CAP_FPS = true;

class Game
{
  public:
    Game();
    ~Game();

    void Initialize();
    void Destroy();
    void Setup();

    void Run();

    void TileMapInit();

    void ProcessInput();
    void Update();
    void Render();

  private:
    struct SDL_Window* window;
    struct SDL_Renderer* renderer;
    void KeyBoardInput();
    void GetDisplayModeDimenesions();

    bool is_running;
    struct SDL_Texture* tank_texture;
    double deltaTime = 0;

    int window_width;
    int window_height;

    int ms_passed = 0;

    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetStore> assetStore;
    void TimeLogic();
};

#endif