#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../Constants/AssetStore.h"
#include "../ECS/System.h"
#include "SDL2/SDL.h"

class RenderSystem : public System
{
  public:
    RenderSystem();
    void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetstore);
    void AddEntityToSystem(Entity entity) override;
};

#endif