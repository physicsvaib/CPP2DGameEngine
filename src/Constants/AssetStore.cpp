#include "AssetStore.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL_image.h>

AssetStore::AssetStore()
{
    Logger::Log("Asset Store Created");
}

AssetStore::~AssetStore()
{
    ClearAssets();
    Logger::Log("Asset Store Destroyed");
}

void AssetStore::ClearAssets()
{
    for (auto texture : textures)
    {
        SDL_DestroyTexture(texture.second);
    }

    textures.clear();
}

void AssetStore::AddTexture(SDL_Renderer* renderer, const PhywSprite& spriteID,
                            const std::string& fileName)
{
    SDL_Surface* imgSurface = IMG_Load((SPRITE_ASSETS_PATH + fileName).c_str());

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imgSurface);
    textures.emplace(spriteID, texture);
    Logger::Log("New texture added " + fileName);
    SDL_FreeSurface(imgSurface);
}

std::pair<int, int> AssetStore::AddTileMap(SDL_Renderer* renderer, const PhywSprite& spriteID,
                                           const std::string& fileName)
{
    SDL_Surface* imgSurface = IMG_Load((fileName).c_str());
    int w = imgSurface->w;
    int h = imgSurface->h;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imgSurface);
    textures.emplace(spriteID, texture);
    Logger::Log("New texture added " + fileName);
    SDL_FreeSurface(imgSurface);

    return std::make_pair(w, h);
}

SDL_Texture* AssetStore::GetTexture(const PhywSprite& spriteID) const
{
    auto it = textures.find(spriteID);
    if (it != textures.end())
    {
        return it->second;
    }
    else
    {
        Logger::Error("Error of finding texture");
        return nullptr;
    }
}
