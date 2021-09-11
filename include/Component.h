#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class GameObject;

class Component
{
protected:
    GameObject& associated;
public:
    Component(GameObject& associated);
    virtual ~Component();
    virtual void Update(float dt);
    virtual void Render();
    virtual bool Is(std::string type);
};

#include "GameObject.h"

#endif