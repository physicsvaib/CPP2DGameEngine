#ifndef TILEMAPSYSTEM_H
#define TILEMAPSYSTEM_H

#include "../Constants/AssetStore.h"
#include "../ECS/System.h"
#include "SDL2/SDL.h"
#include <memory>

class TileMapSystem : public System
{
  public:
    TileMapSystem();
    void Init(std::unique_ptr<AssetStore>& assetstore);
    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetstore);
};

#endif