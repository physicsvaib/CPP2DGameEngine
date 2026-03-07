#include "TileMapSystem.h"
#include "../Components/TileMapComponent.h"
#include "../Logger/Logger.h"

TileMapSystem::TileMapSystem()
{
    RequireComponent<TileMapComponent>();
}

void TileMapSystem::Init(std::unique_ptr<AssetStore>& assetStore)
{
    for (auto entity : GetSystemEntities())
    {
        Logger::Info("Hey there");
        auto tileMap = entity.GetComponent<TileMapComponent>();
        SDL_Texture* texture = assetStore->GetTexture(tileMap.spriteName);
        SDL_QueryTexture(texture, nullptr, nullptr, &tileMap.tileSizeX, &tileMap.tileSizeY);
        Logger::Info("Found " + std::to_string(tileMap.tileSizeX) + " and  " +
                     std::to_string(tileMap.tileSizeY));
    }
}

void TileMapSystem::Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetstore) {}
