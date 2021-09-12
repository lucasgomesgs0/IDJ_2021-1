#ifndef TILESET_H
#define TILESET_H

#include <string>

#include "Sprite.h"

class TileSet
{
private:
    Sprite tileSet;
    int rows, columns;
    int tileWidth, tileHeight;

public:
    TileSet(GameObject &associated, int tileWidth, int tileHeight, std::string file);
    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();
};

#endif