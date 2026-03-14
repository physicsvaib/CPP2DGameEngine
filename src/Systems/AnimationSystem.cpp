#include "AnimationSystem.h"
#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"

AnimationSystem::AnimationSystem()
{
    RequireComponent<SpriteComponent>();
    RequireComponent<AnimationComponent>();
}

void AnimationSystem::Update()
{
    std::string ids = "";
    for (Entity entity : GetSystemEntities())
    {
        SpriteComponent& spriteComp = entity.GetComponent<SpriteComponent>();
        AnimationComponent& animComp = entity.GetComponent<AnimationComponent>();

        animComp.currentFrame =
            static_cast<int>(((SDL_GetTicks() - animComp.startTime) * animComp.frameRate / 1000.0)) %
            animComp.numOfFrames;

        if (animComp.currentFrame >= animComp.numOfFrames)
        {
            animComp.currentFrame = animComp.shouldLoop ? 0 : animComp.numOfFrames - 1;
        }

        int offsetX = animComp.currentFrame * animComp.singleSpriteSize;
        spriteComp.srcRect = SDL_Rect{offsetX, 0, animComp.singleSpriteSize, animComp.singleSpriteSize};
        ids += std::to_string(entity.GetID()) + ", ";
    }

#ifdef DEBUG_SYSTEM
    if (ids != "")
        Logger::Info("Animation System on " + ids);
#endif
}
