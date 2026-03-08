#ifndef TILEMAPCOMPONENT_H
#define TILEMAPCOMPONENT_H

#include "../Constants/SpriteReferences.h"

struct TileMapComponent
{
    PhywSprite spriteName;
    int rows;
    int cols;
    int tileSizeX;
    int tileSizeY;

    TileMapComponent(PhywSprite sprite = PhywSprite::NONE, int rows = 0, int cols = 0,
                     int tileSizeX = 0, int tileSizeY = 0)
    {
        this->spriteName = sprite;
        this->rows = rows;
        this->cols = cols;
        this->tileSizeX = tileSizeX;
        this->tileSizeY = tileSizeY;
    }
};

#endif