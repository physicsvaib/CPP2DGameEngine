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

    AnimationComponent(int numOfFrames, int frameRate, bool shouldLoop)
    {
        this->numOfFrames = numOfFrames;
        this->currentFrame = 1;
        this->frameRate = frameRate;
        this->shouldLoop = shouldLoop;
        this->startTime = SDL_GetTicks();
    }
};

#endif