#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../Constants/SpriteReferences.h"
#include <string>

struct SpriteComponent
{
    PhywSprite image;
    int width;
    int height;
    int zIndex;
    SDL_Rect srcRect;

    SpriteComponent(PhywSprite image = PhywSprite::NONE, int width = 1, int height = 1,
                    int zIndex = 0, int rectX = 0, int rectY = 0, int endX = -1, int endY = -1)
    {
        this->image = image;
        this->height = height;
        this->width = width;
        this->srcRect = {rectX, rectY, endX == -1 ? width : endX, endY == -1 ? height : endY};
        this->zIndex = zIndex;
    }
};

#endif