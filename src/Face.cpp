#include <string.h>
#include <memory>

#include "Face.h"
#include "Sound.h"

Face::Face(GameObject &associated) : Component(associated)
{
    hitPoints = 30;
}

void Face::Damage(int damage)
{
    hitPoints -= damage;

    if (hitPoints <= 0)
    {
        std::unique_ptr<Component> sound = associated.GetComponent("Sound");
        if (sound != nullptr)
        {
            ((Sound *)sound.get())->Play(1);
        }
        associated.RequestDelete();
    }
}

void Face::Update(float dt) {}
void Face::Render() {}

bool Face::Is(std::string type)
{
    return strcmp(type.c_str(), "Face") == 0;
}