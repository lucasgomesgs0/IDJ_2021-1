#include "TileSet.h"

#include <iostream>

TileSet::TileSet(GameObject &associated, int tileWidth, int tileHeight, std::string file) : tileSet(associated, file)
{
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;

    if (tileSet.IsOpen())
    {
        columns = tileSet.GetWidth() / tileWidth;
        rows = tileSet.GetHeight() / tileHeight;
    }
    else
    {
        std::cout << "Unable to load the tileset: " << file << std::endl;
        columns = 0;
        rows = 0;
    }
}

void TileSet::RenderTile(unsigned index, int x, int y)
{
    if (index < (unsigned)rows * columns - 1)
    {
        tileSet.SetClip((index % columns) * tileWidth, (index / columns) * tileHeight, tileWidth, tileHeight);
        tileSet.Render(x, y);
    }
}

int TileSet::GetTileWidth()
{
    return tileWidth;
}

int TileSet::GetTileHeight()
{
    return tileHeight;
}