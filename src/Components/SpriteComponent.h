#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>

struct SpriteComponent
{
    // std::string imagePath;
    int width;
    int height;

    SpriteComponent(int width = 1, int height = 1)
    {
        this->height = height;
        this->width = width;
    }
};

#endif