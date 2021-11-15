#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>

#define A_KEY SDLK_a
#define D_KEY SDLK_d
#define W_KEY SDLK_w
#define S_KEY SDLK_s
#define ESCAPE_KEY SDLK_ESCAPE
#define SPACE_KEY SDLK_SPACE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

#define INCLUDE_SDL
#include "SDL_include.h"

class InputManager
{
private:
    bool mouseState[6];
    int mouseUpdate[6];

    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;

    bool quitRequested;
    
    int updateCounter;

    int mouseX, mouseY;
public:
    InputManager();
    ~InputManager();

    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

    static InputManager& GetInstance();
};

#endif