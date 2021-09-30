#include <iostream>
#include <string.h>

#include "Sound.h"

Sound::Sound(GameObject &associated) : Component(associated)
{
    chunk = nullptr;
}

Sound::Sound(GameObject &associated, std::string file) : Sound(associated)
{
    Open(file);
}

Sound::~Sound()
{
    if (chunk != nullptr)
    {
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times)
{
    if (chunk == nullptr)
    {
        std::cout << "Unable to play the music" << std::endl;
        std::cout << "Error: " << Mix_GetError() << std::endl;
    }
    else
    {
        channel = Mix_PlayChannel(-1, chunk, times - 1);
        if (channel == -1)
        {
            SDL_Log("Unable to play the music: %s", Mix_GetError());
        }
    }
}

void Sound::Stop()
{
    if (chunk != nullptr)
    {
        Mix_HaltChannel(channel);
    }
}

bool Sound::IsOpen()
{
    return chunk != nullptr;
}

void Sound::Open(std::string file)
{
    chunk = Mix_LoadWAV(file.c_str());

    if (chunk == nullptr)
    {
        std::cout << "Unable to load the sound: " << file.c_str() << std::endl;
        std::cout << "Error: " << Mix_GetError() << std::endl;
    }
}

void Sound::Update(float dt) {}

void Sound::Render() {}

bool Sound::Is(std::string type)
{
    return strcmp(type.c_str(), "Sound") == 0;
}