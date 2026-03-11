#include "AnimationSystem.h"
#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"

AnimationSystem::AnimationSystem()
{
    RequireComponent<SpriteComponent>();
    RequireComponent<AnimationComponent>();
    RequireComponent<TransformComponent>();
}

void AnimationSystem::Update(double deltaTime)
{
    for (Entity entity : GetSystemEntities())
    {
        SpriteComponent spriteComp = entity.GetComponent<SpriteComponent>();
        AnimationComponent animComp = entity.GetComponent<AnimationComponent>();
        TransformComponent transformComp = entity.GetComponent<TransformComponent>();

        animComp.currentFrame += 1;

        if (animComp.currentFrame >= animComp.numOfFrames)
        {
            if (animComp.shouldLoop)
            {
                animComp.currentFrame = 0;
            }
        }

        int offsetX = animComp.currentFrame * animComp.singleSpriteSize;
        spriteComp.srcRect =
            SDL_Rect{offsetX, 0, animComp.singleSpriteSize, animComp.singleSpriteSize};

        // osset = currentFrame
        // offset = (currentFrame %  frameRate) % totalFrames
        // offset *= singleSize
        // animComp.frameRate
    }
}
