#include "game.h"
#include "menu.h"

using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "SNAKE";
SDL_Event e;
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	srand((unsigned int)time(0));
	SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	intro(renderer);
	startMenu(renderer);
	bool running = true;

	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quitSDL(window, renderer);
				running = false;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					quitSDL(window, renderer);
					running = false;
				}

				else
				{
					if (e.key.keysym.sym == SDLK_1)
					{
						startGame(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, e);
					}
					else
					{
						if (e.key.keysym.sym == SDLK_2)
						{
							quitSDL(window, renderer);
							running = false;
						}
					}
				}
			}
		}
	}
	return 0;
}