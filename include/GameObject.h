#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <memory>

#include "Component.h"
#include "Rect.h"

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
    void AddComponent(std::unique_ptr<Component> cpt);
    void RemoveComponent(std::unique_ptr<Component> cpt);
    std::unique_ptr<Component> GetComponent(std::string type);
};

#endif