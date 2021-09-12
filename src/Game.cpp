#include "Game.h"
#include "State.h"
#include "Resources.h"

#include <cstdlib>
#include <ctime>

Game *Game::instance;

Game::Game(std::string title, int width, int height)
{
	if (instance != nullptr)
	{
		SDL_Log("Class has already been instantiated");
		exit(EXIT_FAILURE);
	}

	instance = this;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0)
	{
		SDL_Log("Unable to initialize IMG: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC) == 0)
	{
		SDL_Log("Unable to initialize MIX: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
	{
		SDL_Log("Unable to initialize the OpenAudio: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	Mix_AllocateChannels(32);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

	if (window == nullptr)
	{
		SDL_Log("Unable to create the window: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (Game::renderer == nullptr)
	{
		SDL_Log("Unable to create the renderer: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	state = new State();

	srand(time(NULL));
}

Game::~Game()
{
	delete state;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();

	SDL_Quit();
}

void Game::Run()
{
	while (!state->QuitRequested())
	{
		state->Update(1);
		state->Render();

		SDL_RenderPresent(renderer);

		SDL_Delay(33);
	}
	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();

}

SDL_Renderer *Game::GetRenderer()
{
	return renderer;
}

State &Game::GetState()
{
	return *state;
}

Game &Game::GetInstance()
{
	if (instance != nullptr)
	{
		return *instance;
	}

	instance = new Game("Lucas Gomes Silva - 16/0133505", 1024, 600);

	return *instance;
}
