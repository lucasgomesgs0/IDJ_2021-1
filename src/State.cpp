#include "State.h"

State::State()
{
    quitRequested = false;
    
    bg.Open("assets/img/ocean.jpg");
    music.Open("assets/audio/stageState.ogg");
}

void State::LoadAssets()
{
}

void State::Update(float dt)
{
    quitRequested = SDL_QuitRequested();
}

void State::Render()
{
    bg.Render(0, 0);
    music.Play();
}

bool State::QuitRequested()
{
    return quitRequested;
}