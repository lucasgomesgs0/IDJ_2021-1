#include "InputManager.h"

InputManager &InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

InputManager::InputManager()
{
    for (int i = 0; i < 6; i++)
    {
        mouseState[i] = -1;
        mouseUpdate[i] = -1;
    }

    updateCounter = 0;
    quitRequested = false;
    mouseX = -1;
    mouseY = -1;
}

InputManager::~InputManager()
{
    keyState.clear();
    keyUpdate.clear();
}

void InputManager::Update()
{
    SDL_Event event;
    updateCounter++;
    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;

    while (SDL_PollEvent(&event))
    {
        if (event.key.repeat != 1)
        {
            if (event.type == SDL_KEYDOWN)
            {
                keyState[event.key.keysym.sym] = true;
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }

            if (event.type == SDL_KEYUP)
            {
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                mouseState[event.button.button] = true;
                mouseUpdate[event.key.keysym.sym] = updateCounter;
            }

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                mouseState[event.button.button] = false;
                mouseUpdate[event.key.keysym.sym] = updateCounter;
            }

            if (event.type == SDL_QUIT)
            {
                quitRequested = true;
            }
        }
    }
}

bool InputManager::KeyPress(int key)
{
    return keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key)
{
    return !keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key)
{
    return keyState[key];
}

bool InputManager::MousePress(int button)
{
    return mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button)
{
    return !mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button)
{
    return mouseState[button];
}

int InputManager::GetMouseX()
{
    return mouseX;
}

int InputManager::GetMouseY()
{
    return mouseY;
}

bool InputManager::QuitRequested()
{
    return quitRequested;
}