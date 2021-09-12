#include "Music.h"

#include <iostream>

Music::Music()
{
    music = nullptr;
}

Music::Music(std::string file)
{
    music = nullptr;
    Open(file);
}

Music::~Music()
{
    Mix_FreeMusic(music);
}

void Music::Play(int times)
{
    if (music == nullptr)
    {
        std::cout << "Unable to play the music" << std::endl;
        std::cout << "Error: " << Mix_GetError() << std::endl;
    }
    else
    {
        if (Mix_PlayMusic(music, times) != 0)
        {
            SDL_Log("Unable to play the music: %s", Mix_GetError());
        }
    }
}

void Music::Stop(int msToStop = 1500)
{
    if (!Mix_FadeOutMusic(msToStop))
    {
        std::cout << "Error when tried fade music out" << std::endl;
        std::cout << "Error: " << Mix_GetError() << std::endl;
    }
}

void Music::Open(std::string file)
{
    music = Mix_LoadMUS(file.c_str());

    if (music == nullptr)
    {
        std::cout << "Unable to load the music: " << file.c_str() << std::endl;
        std::cout << "Error: " << Mix_GetError() << std::endl;
    }
}

bool Music::IsOpen()
{
    return music != nullptr;
}