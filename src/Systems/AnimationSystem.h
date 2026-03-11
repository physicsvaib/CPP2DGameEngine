#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include "../ECS/System.h"

class AnimationSystem : public System
{
  public:
    AnimationSystem();
    void Update(double deltaTime);
    void UpdateAnimationFrame();
};

#endif