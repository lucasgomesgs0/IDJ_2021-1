#include "Camera.h"
#include "InputManager.h"

GameObject* Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed;

void Camera::Follow(GameObject *newFocus)
{
    focus = newFocus;
}

void Camera::Unfollow()
{
    focus = nullptr;
}

void Camera::Update(float dt)
{
    if (focus != nullptr)
    {
        pos.x = focus->box.x + focus->box.w - 1024 / 2;
        pos.y = focus->box.y + focus->box.h - 600 / 2;
    }
    else
    {
        InputManager &inputManager = InputManager::GetInstance();

        if (inputManager.IsKeyDown(D_KEY))
        {
            speed.x = 100;
        }
        else if (inputManager.IsKeyDown(A_KEY))
        {
            speed.x = -100;
        }
        else
        {
            speed.x = 0;
        }

        if (inputManager.IsKeyDown(W_KEY))
        {
            speed.y = 100;
        }
        else if (inputManager.IsKeyDown(S_KEY))
        {
            speed.y = -100;
        }
        else
        {
            speed.y = 0;
        }
    
        pos.x += speed.x * dt;
        pos.y += speed.y * dt;
    }
}