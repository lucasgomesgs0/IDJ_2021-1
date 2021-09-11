#ifndef FACE_H
#define FACE_H

#include <string>

#include "GameObject.h"
#include "Component.h"

class Face : public Component
{
private:
    int hitPoints;
public:
    Face(GameObject& associated);

    void Damage(int damage);

    void Update(float dt);
    void Render();
    bool Is(std::string type);
};



#endif