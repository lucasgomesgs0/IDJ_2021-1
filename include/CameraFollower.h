#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "GameObject.h"
#include "Component.h"

class CameraFollower : public Component
{
private:

    
public: 
    CameraFollower(GameObject &go);

    void Update(float dt);
    void Render();
    bool Is(std::string type);
};

#endif
