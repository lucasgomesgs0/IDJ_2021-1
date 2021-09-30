#include <algorithm>

#include "GameObject.h"
#include <iostream>
GameObject::GameObject()
{
    isDead = false;
}

GameObject::~GameObject()
{
    for (auto it = components.begin(); it != components.end(); it++)
    {
        // when iterate from end to begin, the program break when use reset
        // release without return to any variable will cause leak, using reset wil break the program
        // using reset when iterate from begin to end, the sound doesn't plays

        Component* aux = it->release();
    }
    components.clear();
}

void GameObject::Update(float dt)
{
    for (size_t i = 0; i < components.size(); i++)
    {
        components[i]->Update(dt);
    }
}

void GameObject::Render()
{
    for (size_t i = 0; i < components.size(); i++)
    {
        components[i]->Render();
    }
}

bool GameObject::IsDead()
{
    return isDead;
}

void GameObject::RequestDelete()
{
    isDead = true;
}

void GameObject::AddComponent(Component *cpt)
{
    components.emplace_back(std::move(cpt));
}

void GameObject::RemoveComponent(Component *cpt)
{
    for (size_t i = 0; i < components.size(); i++)
    {
        if (components[i].get() == cpt)
        {
            components.erase(components.begin() + i);
            break;
        }
    }
}

Component *GameObject::GetComponent(std::string type)
{
    for (auto it = components.begin(); it != components.end(); it++)
    {
        if ((*it)->Is(type))
        {
            return (*it).get();
        }
    }
    return nullptr;
}
