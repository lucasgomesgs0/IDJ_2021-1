#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

#include "Component.h"
#include "Rect.h"

class GameObject
{
private:
    std::vector<Component *> components;
    bool isDead;

public:
    Rect box;
    GameObject();
    ~GameObject();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component *cpt);
    void RemoveComponent(Component *cpt);
    Component *GetCompoennt(std::string type);
};

#endif