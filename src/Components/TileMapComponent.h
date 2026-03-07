#ifndef TILEMAPCOMPONENT_H
#define TILEMAPCOMPONENT_H

#include "../Constants/SpriteReferences.h"

struct TileMapComponent
{
    PhywSprite spriteName;
    std::string mapPath;
    int rows;
    int cols;
    int tileSizeX;
    int tileSizeY;

    TileMapComponent(PhywSprite sprite = PhywSprite::NONE, std::string mapPath = "", int rows = 0,
                     int cols = 0)
    {
        this->spriteName = sprite;
        this->mapPath = mapPath;
        this->rows = rows;
        this->cols = cols;
    }
};

#endif