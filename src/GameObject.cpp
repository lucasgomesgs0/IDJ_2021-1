#include <algorithm>

#include "GameObject.h"

GameObject::GameObject()
{
    isDead = false;
}

GameObject::~GameObject()
{
    // for (auto it = components.begin(); it != components.end(); it++)
    // {
    //     delete it;
    // }
    components.clear();
}

void GameObject::Update(float dt)
{
    for (auto it = components.begin(); it != components.end(); it++)
    {
        (*it)->Update(dt);
    }
}

void GameObject::Render()
{
    for (auto it = components.begin(); it != components.end(); it++)
    {
        (*it)->Render();
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
    for (size_t i = 0; i < components.size(); i++){
		if (components[i] == cpt) {
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
            return std::move(*it);
        }
    }
    return nullptr;
}
