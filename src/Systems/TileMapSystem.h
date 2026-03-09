#ifndef TILEMAPSYSTEM_H
#define TILEMAPSYSTEM_H

#include "../Constants/AssetStore.h"
#include "../ECS/System.h"
#include "SDL2/SDL.h"
#include <memory>

struct TileMapComponent;

class TileMapSystem : public System
{
  public:
    TileMapSystem(std::string path = "", int rows = 0, int cols = 0);
    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetstore);

  private:
    void MakeCell(const TileMapComponent& tileMap, SDL_Renderer* renderer, SDL_Texture* texture,
                  int x, int y, int locX, int locY);
    int tileSize = 32;
    double tileScale = 3.0;
};

#endif