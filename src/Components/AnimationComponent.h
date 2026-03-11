#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "SDL2/SDL.h"

struct AnimationComponent
{

    int numOfFrames;
    int currentFrame;
    int frameRate;
    bool shouldLoop;
    int startTime;
    int singleSpriteSize;

    AnimationComponent(int numOfFrames = 1, int frameRate = 1, bool shouldLoop = true,
                       int singleSpriteSize = 32)
    {
        this->numOfFrames = numOfFrames;
        this->currentFrame = 1;
        this->frameRate = frameRate;
        this->shouldLoop = shouldLoop;
        this->singleSpriteSize = singleSpriteSize;
        this->startTime = SDL_GetTicks();
    }
};

#endif