#include <math.h>

#include "State.h"
#include "Sprite.h"
#include "Sound.h"
#include "Face.h"

State::State()
{
    quitRequested = false;

    std::unique_ptr<GameObject> go = std::unique_ptr<GameObject>(new GameObject());
	std::unique_ptr<Sprite> sprite = std::unique_ptr<Sprite>(new Sprite(*go, "assets/img/ocean.jpg"));
	go->box.x = 0;
	go->box.y = 0;
	go->AddComponent(std::move(sprite));
	objectArray.emplace_back(std::move(go));

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
    Input();

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

    std::unique_ptr<Sprite> sprite = std::unique_ptr<Sprite>(new Sprite(*go, "assets/img/penguinface.png"));

    go->box.x = mouseX - sprite->GetWidth() / 2;
    go->box.y = mouseY - sprite->GetHeight() / 2;

    go->AddComponent(std::move(sprite));

    std::unique_ptr<Sound> sound = std::unique_ptr<Sound>(new Sound(*go, "assets/audio/boom.wav"));
    go->AddComponent(std::move(sound));

    std::unique_ptr<Face> face = std::unique_ptr<Face>(new Face(*go));
    go->AddComponent(std::move(face));

    objectArray.emplace_back(std::move(go));
}

void State::Input()
{
    SDL_Event event;
    int mouseX, mouseY;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event))
    {

        // Se o evento for quit, setar a flag para terminação
        if (event.type == SDL_QUIT)
        {
            quitRequested = true;
        }

        // Se o evento for clique...
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {

            // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
            for (int i = objectArray.size() - 1; i >= 0; --i)
            {
                // Obtem o ponteiro e casta pra Face.
                GameObject *go = (GameObject *)objectArray[i].get();
                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
                // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
                // ao usar get(), violamos esse princípio e estamos menos seguros.
                // Esse código, assim como a classe Face, é provisório. Futuramente, para
                // chamar funções de GameObjects, use objectArray[i]->função() direto.

                if (go->box.Contains({(float)mouseX, (float)mouseY}))
                {
                    Face *face = (Face *)go->GetComponent("Face").get();
                    if (nullptr != face)
                    {
                        // Aplica dano
                        face->Damage(std::rand() % 10 + 10);
                        // Sai do loop (só queremos acertar um)
                        break;
                    }
                }
            }
        }
        if (event.type == SDL_KEYDOWN)
        {
            // Se a tecla for ESC, setar a flag de quit
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                quitRequested = true;
            }
            // Se não, crie um objeto
            else
            {
                Vec2 objPos = Vec2(200, 0).GetRotated(-M_PI + M_PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}