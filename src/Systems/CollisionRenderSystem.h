#ifndef COLLISIONRENDERSYSTEM_H
#define COLLISIONRENDERSYSTEM_H

#include "../ECS/System.h"

class SDL_Renderer;

class CollisionRenderSystem : public System
{
  public:
    CollisionRenderSystem();
    void Update(SDL_Renderer* renderer);
};

#endif