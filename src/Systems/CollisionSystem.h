#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/System.h"
class SDL_Renderer;

class CollisionSystem : public System
{
  public:
    CollisionSystem();
    void Update();
};

#endif