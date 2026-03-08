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
    TileMapSystem(std::string path);
    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetstore);

  private:
    void MakeCell(const TileMapComponent& tileMap, SDL_Renderer* renderer, SDL_Texture* texture,
                  int index, int locX, int locY);
};

#endif