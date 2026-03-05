#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include "SpriteReferences.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>

class AssetStore
{
  private:
    std::map<PhywSprite, SDL_Texture*> textures;

  public:
    AssetStore();
    ~AssetStore();

    void ClearAssets();
    void AddTexture(const PhywSprite& spriteID, const std::string& filePath);
    SDL_Texture* GetTexture(const PhywSprite& spriteID) const;
};

#endif