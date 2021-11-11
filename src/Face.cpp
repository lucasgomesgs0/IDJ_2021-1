#include <string.h>
#include <memory>

#include "Face.h"
#include "Sound.h"
#include "InputManager.h"

Face::Face(GameObject &associated) : Component(associated)
{
    hitPoints = 30;
}

void Face::Damage(int damage)
{
    hitPoints -= damage;

    if (hitPoints <= 0)
    {
        Sound *sound = (Sound *)associated.GetComponent("Sound");
        if (sound != nullptr)
        {
            sound->Play(1);
        }
        associated.RequestDelete();
    }
}

void Face::Update(float dt)
{
    InputManager &inputManager = InputManager::GetInstance();

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON) && associated.box.Contains({(float)inputManager.GetMouseX(), (float)inputManager.GetMouseY()}))
    {
        Damage(std::rand() % 10 + 10);
    }
}

void Face::Render() {}

bool Face::Is(std::string type)
{
    return strcmp(type.c_str(), "Face") == 0;
}