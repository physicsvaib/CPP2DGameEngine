#include "AssetStore.h"
#include "../Logger/Logger.h"

AssetStore::AssetStore()
{
    Logger::Log("Asset Store Created");
}

AssetStore::~AssetStore()
{
    Logger::Log("Asset Store Destroyed");
}

void AssetStore::ClearAssets() {}

void AssetStore::AddTexture(const PhywSprite& spriteID, const std::string& filePath) {}

SDL_Texture* AssetStore::GetTexture(const PhywSprite& spriteID) const
{
    return nullptr;
}
