#include "TileMapSystem.h"
#include "../Components/TileMapComponent.h"
#include "../Logger/Logger.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> vecs;

std::vector<std::string> readFileLines(const std::string& path)
{
    std::ifstream f(path);
    std::vector<std::string> lines;
    for (std::string line; std::getline(f, line);)
        lines.push_back(line);
    return lines;
}

std::vector<int> parseLineToInts(const std::string& line)
{
    std::vector<int> row;
    std::stringstream ss(line);
    std::string value;
    while (std::getline(ss, value, ','))
    {
        row.push_back(std::stoi(value));
    }
    return row;
}

std::vector<std::vector<int>> loadGrid(const std::string& path)
{
    std::vector<std::string> lines = readFileLines(path);
    std::vector<std::vector<int>> grid;
    for (const auto& line : lines)
        grid.push_back(parseLineToInts(line));
    return grid;
}

TileMapSystem::TileMapSystem(std::string path)
{
    RequireComponent<TileMapComponent>();

    Logger::Warning("Hello Tile Map");
    auto grid = loadGrid(path);

    for (const auto& row : grid)
    {
        std::vector<int> vec;
        for (int val : row)
        {
            vec.push_back(val);
        }
        vecs.push_back(vec);
    }
}

void TileMapSystem::Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetstore)
{
    for (auto entity : GetSystemEntities())
    {
        TileMapComponent tileMap = entity.GetComponent<TileMapComponent>();
        SDL_Texture* texture = assetstore->GetTexture(tileMap.spriteName);

        for (int i = 0; i < vecs.size(); i++)
        {
            for (int j = 0; j < vecs[i].size(); j++)
            {
                MakeCell(tileMap, renderer, texture, vecs[i][j], i * 160, j * 160);
            }
        }
    }
}

void TileMapSystem::MakeCell(const TileMapComponent& tileMap, SDL_Renderer* renderer,
                             SDL_Texture* texture, int index, int locX, int locY)
{
    int cellX = tileMap.tileSizeX / tileMap.rows;
    int cellY = tileMap.tileSizeY / tileMap.cols;
    int x = index / tileMap.cols;
    int y = index % tileMap.cols;
    SDL_Rect src{x * cellX, y * cellY, cellX, cellY};
    SDL_Rect dst{locX, locY, cellX * 5, cellY * 5};
    SDL_RenderCopy(renderer, texture, &src, &dst);
}
