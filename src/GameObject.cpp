#include <algorithm>

#include "GameObject.h"

GameObject::GameObject()
{
    isDead = false;
}

GameObject::~GameObject()
{
    for (auto it = components.end(); it != components.begin(); it--)
    {
        delete it->get();
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

void GameObject::AddComponent(std::unique_ptr<Component> cpt)
{
    components.emplace_back(std::move(cpt));
}

void GameObject::RemoveComponent(std::unique_ptr<Component> cpt)
{
    for (size_t i = 0; i < components.size(); i++)
    {
        if (components[i] == cpt)
        {
            components.erase(components.begin() + i);
            break;
        }
    }
}

std::unique_ptr<Component> GameObject::GetComponent(std::string type)
{
    for (auto it = components.begin(); it != components.end(); it++)
    {
        if ((*it)->Is(type))
        {
            return (std::unique_ptr<Component>)it->get();
        }
    }
    return nullptr;
}
