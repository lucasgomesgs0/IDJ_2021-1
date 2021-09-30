#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <memory>

#include "Rect.h"

class Component;

class GameObject
{
private:
    std::vector<std::unique_ptr<Component>> components;
    bool isDead;

public:
    Rect box;
    GameObject();
    ~GameObject();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string type);
};

#include "Component.h"
#endif