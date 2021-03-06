#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Vec2.h"

#define SPEED 150

class Camera
{
private:
    static GameObject *focus;
    
public: 
    static Vec2 pos, speed;

    static void Follow(GameObject *newFocus);
    static void Unfollow();
    static void Update(float dt);
};
#endif
