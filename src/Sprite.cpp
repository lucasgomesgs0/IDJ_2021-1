#include "Sprite.h"
#include "Game.h"

#include <iostream>

Sprite::Sprite()
{
    texture = nullptr;
}

Sprite::Sprite(std::string file)
{
    texture = nullptr;

    Sprite::Open(file);
}

Sprite::~Sprite()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file)
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }

    Game &instance = Game::GetInstance();
    texture = IMG_LoadTexture(instance.GetRenderer(), file.c_str());

    if (texture == nullptr)
    {
        std::cout << "Unable to load the texture: " << file.c_str() << std::endl;
        std::cout << "Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0)
        {
            SDL_Log("Unable to get the texture parameters: %s", IMG_GetError());
            exit(EXIT_FAILURE);
        }

        Sprite::SetClip(0, 0, width, height);
    }
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y)
{
    SDL_Rect *dstRect = new SDL_Rect();

    dstRect->x = x;
    dstRect->y = y;
    dstRect->w = clipRect.w;
    dstRect->h = clipRect.h;

    Game &instance = Game::GetInstance();
    SDL_RenderCopy(instance.GetRenderer(), texture, &clipRect, dstRect);
}

int Sprite::GetWidth()
{
    return width;
}

int Sprite::GetHeight()
{
    return height;
}

bool Sprite::IsOpen()
{
    return texture != nullptr;
}