#include "TileMapSystem.h"
#include "../Components/TileMapComponent.h"
#include "../Logger/Logger.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<std::pair<int, int>>> vecs;

TileMapSystem::TileMapSystem(std::string path, int rows, int cols)
{
    RequireComponent<TileMapComponent>();

    Logger::Warning("Hello Tile Map");

    std::fstream mapFile;
    mapFile.open(path);

    for (int y = 0; y < rows; y++)
    {
        std::vector<std::pair<int, int>> vec;
        for (int x = 0; x < cols; x++)
        {
            char ch;
            mapFile.get(ch);
            int chY = std::atoi(&ch);
            mapFile.get(ch);
            int chX = std::atoi(&ch);
            mapFile.ignore();
            vec.push_back(std::make_pair(chY, chX));
        }
        vecs.push_back(vec);
    }
}

void TileMapSystem::Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetstore)
{
    // Logger::Warning("Tiling the tilemap");
    for (auto entity : GetSystemEntities())
    {
        TileMapComponent tileMap = entity.GetComponent<TileMapComponent>();
        SDL_Texture* texture = assetstore->GetTexture(tileMap.spriteName);

        for (size_t i = 0; i < vecs.size(); i++)
        {
            for (size_t j = 0; j < vecs[i].size(); j++)
            {
                MakeCell(tileMap, renderer, texture, vecs[i][j].second, vecs[i][j].first, j, i);
            }
        }
    }
}

void TileMapSystem::MakeCell(const TileMapComponent& tileMap, SDL_Renderer* renderer, SDL_Texture* texture, int x,
                             int y, int locX, int locY)
{
    SDL_Rect src{x * tileSize, y * tileSize, tileSize, tileSize};
    SDL_Rect dst{static_cast<int>(locX * tileScale * tileSize), static_cast<int>(locY * tileScale * tileSize),
                 static_cast<int>(tileSize * tileScale), static_cast<int>(tileScale * tileSize)};
    SDL_RenderCopy(renderer, texture, &src, &dst);
}
