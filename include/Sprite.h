#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL

#include "SDL_include.h"
#include "Component.h"

#include <string>

class Sprite : public Component
{
private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;

public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, std::string file);
    ~Sprite();
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render();
    int GetWidth();
    int GetHeight();
    bool IsOpen();
};

#endif