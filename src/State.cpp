#include <math.h>

#include "State.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"

State::State()
{
    quitRequested = false;

    std::unique_ptr<GameObject> go_background = std::unique_ptr<GameObject>(new GameObject());
    Sprite* sprite = new Sprite(*go_background, "assets/img/ocean.jpg");
	CameraFollower *cameraFollower = new CameraFollower(*go_background);
    go_background->box.x = 0;
    go_background->box.y = 0;
    go_background->AddComponent(sprite);
    go_background->AddComponent(cameraFollower);
    objectArray.emplace_back(std::move(go_background));

    std::unique_ptr<GameObject> go_tileMap = std::unique_ptr<GameObject>(new GameObject());
    go_tileMap->box.x = 0;
    go_tileMap->box.y = 0;
    TileSet* tileSet = new TileSet(*go_tileMap, 64, 64, "assets/img/tileset.png");
    TileMap* tileMap = new TileMap(*go_tileMap, "assets/map/tileMap.txt", tileSet);
    go_tileMap->AddComponent(tileMap);
    objectArray.emplace_back(std::move(go_tileMap));

    music.Open("assets/audio/stageState.ogg");
    music.Play(-1);
}

State::~State()
{
    objectArray.clear();
}

void State::LoadAssets()
{
}

void State::Update(float dt)
{
    InputManager& inputManager = InputManager::GetInstance();

    Camera::Update(dt);

    if (inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}

    if (inputManager.KeyPress(SPACE_KEY)) {
        Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI * (rand() % 1001) / 500.0) + Vec2(inputManager.GetMouseX(), inputManager.GetMouseY());
        AddObject((int)objPos.x, (int)objPos.y);
	}

    for (size_t i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
    }

    for (size_t i = 0; i < objectArray.size(); i++)
    {
        if (objectArray[i]->IsDead())
        {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render()
{
    for (size_t i = 0; i < objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested()
{
    return quitRequested;
}

void State::AddObject(int mouseX, int mouseY)
{
    std::unique_ptr<GameObject> go = std::unique_ptr<GameObject>(new GameObject());

    Sprite* sprite = new Sprite(*go, "assets/img/penguinface.png");

    go->box.x = mouseX - sprite->GetWidth() / 2 + Camera::pos.x;
    go->box.y = mouseY - sprite->GetHeight() / 2 + Camera::pos.y;

    go->AddComponent(sprite);

    Sound* sound = new Sound(*go, "assets/audio/boom.wav");
    go->AddComponent(sound);

    Face* face = new Face(*go);
    go->AddComponent(face);

    objectArray.emplace_back(std::move(go));
}

// void State::Input()
// {
//     SDL_Event event;
//     int mouseX, mouseY;

//     // Obtenha as coordenadas do mouse
//     SDL_GetMouseState(&mouseX, &mouseY);

//     // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contr??rio
//     while (SDL_PollEvent(&event))
//     {

//         // Se o evento for quit, setar a flag para termina????o
//         if (event.type == SDL_QUIT)
//         {
//             quitRequested = true;
//         }

//         // Se o evento for clique...
//         if (event.type == SDL_MOUSEBUTTONDOWN)
//         {

//             // Percorrer de tr??s pra frente pra sempre clicar no objeto mais de cima
//             for (int i = objectArray.size() - 1; i >= 0; --i)
//             {
//                 // Obtem o ponteiro e casta pra Face.
//                 GameObject *go = (GameObject *)objectArray[i].get();
//                 // Nota: Desencapsular o ponteiro ?? algo que devemos evitar ao m??ximo.
//                 // O prop??sito do unique_ptr ?? manter apenas uma c??pia daquele ponteiro,
//                 // ao usar get(), violamos esse princ??pio e estamos menos seguros.
//                 // Esse c??digo, assim como a classe Face, ?? provis??rio. Futuramente, para
//                 // chamar fun????es de GameObjects, use objectArray[i]->fun????o() direto.

//                 if (go->box.Contains({(float)mouseX, (float)mouseY}))
//                 {
//                     Face *face = (Face *)go->GetComponent("Face");
//                     if (nullptr != face)
//                     {
//                         // Aplica dano
//                         face->Damage(std::rand() % 10 + 10);
//                         // Sai do loop (s?? queremos acertar um)
//                         break;
//                     }
//                 }
//             }
//         }
//         if (event.type == SDL_KEYDOWN)
//         {
//             // Se a tecla for ESC, setar a flag de quit
//             if (event.key.keysym.sym == SDLK_ESCAPE)
//             {
//                 quitRequested = true;
//             }
//             // Se n??o, crie um objeto
//             else
//             {
//                 Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
//                 AddObject((int)objPos.x, (int)objPos.y);
//             }
//         }
//     }
// }