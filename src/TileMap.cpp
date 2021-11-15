#include <string.h>
#include <iostream>
#include <fstream>

#include "TileMap.h"
#include "Camera.h"

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet) : Component(associated)
{
    this->tileSet = tileSet;
    Load(file);
}

void TileMap::Load(std::string file)
{
    int buffer;
    FILE *mapFile = fopen(file.c_str(), "r");

    if (mapFile != NULL)
    {
        fscanf(mapFile, "%d,%d,%d,", &mapWidth, &mapHeight, &mapDepth);

        for (int i = 0; i < mapDepth; i++)
        {
            for (int j = 0; j < mapHeight; j++)
            {
                for (int k = 0; k < mapWidth; k++)
                {
                    fscanf(mapFile, "%d,", &buffer);
                    tileMatrix.push_back(buffer - 1);
                }
            }
        }

        fclose(mapFile);
    }
    else
    {
        std::cout << "Unable to load the tilemap: " << file << std::endl;
    }
}

void TileMap::SetTileSet(TileSet *tileSet)
{
    this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z)
{
    return tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight];
}

void TileMap::Render()
{
    for (int i = 0; i < mapDepth; i++)
    {
        RenderLayer(i, Camera::pos.x, Camera::pos.y);
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {

            tileSet->RenderTile(tileMatrix[j + i * mapWidth + layer * mapWidth * mapHeight], j * tileSet->GetTileWidth() + cameraX, i * tileSet->GetTileHeight() + cameraY);
        }
    }
}

int TileMap::GetWidth()
{
    return mapWidth;
}

int TileMap::GetHeight()
{
    return mapHeight;
}

int TileMap::GetDepth()
{
    return mapDepth;
}

void TileMap::Update(float dt) {}

bool TileMap::Is(std::string type)
{
    return strcmp(type.c_str(), "TileMap") == 0;
}