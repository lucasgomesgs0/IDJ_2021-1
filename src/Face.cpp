#include <string.h>

#include "Face.h"

Face::Face(GameObject &associated) : Component(associated)
{
    hitPoints = 30;
}

void Face::Damage(int damage)
{
    hitPoints -= damage;

    if (hitPoints <= 0)
    {
        associated.RequestDelete();
    }
}

void Face::Update(float dt) {}
void Face::Render() {}

bool Face::Is(std::string type)
{
    return strcmp(type.c_str(), "Face") == 0;
}