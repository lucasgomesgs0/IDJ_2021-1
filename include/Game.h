#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

#include "State.h"

#include <string>

class Game
{
private:
	static Game *instance;
	SDL_Window *window;
	SDL_Renderer *renderer;
	State *state;

public:
	Game(std::string title, int width, int height);
	~Game();
	void Run();
	SDL_Renderer *GetRenderer();
	State &GetState();
	static Game &GetInstance();
};
#endif
