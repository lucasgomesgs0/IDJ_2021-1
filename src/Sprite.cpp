#include "Sprite.h"
#include "Game.h"

#include <iostream>
#include <string.h>

Sprite::Sprite(GameObject &associated) : Component(associated)
{
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, std::string file) : Component(associated)
{
    texture = nullptr;

    Open(file);
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

void Sprite::Render()
{
    Render(associated.box.x, associated.box.y);
}

void Sprite::Render(int x, int y)
{
    SDL_Rect dstRect;

    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;

    associated.box.w = clipRect.w;
    associated.box.h = clipRect.h;

    Game &instance = Game::GetInstance();
    SDL_RenderCopy(instance.GetRenderer(), texture, &clipRect, &dstRect);
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

void Sprite::Update(float dt) {}

bool Sprite::Is(std::string type)
{
    return strcmp(type.c_str(), "Sprite") == 0;
}