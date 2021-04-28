
#include "game.h"
#include "menu.h"
#include <vector>
#include <iostream>
#include <string>
#include <SDL_image.h>

SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string file_path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(file_path.c_str());
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);
	return newTexture;
};
void FillBackground(SDL_Renderer* renderer, SDL_Texture* background)
{
	SDL_RenderCopy(renderer, background, NULL, NULL);

	SDL_RenderPresent(renderer);
}
void DropFood(SDL_Renderer* renderer, SDL_Rect rectangle, SDL_Texture* apple)
{
	SDL_RenderCopy(renderer, apple, NULL, &rectangle);
	SDL_RenderPresent(renderer);
}
void UpdateScore(SDL_Renderer* renderer, int score, TTF_Font* font)
{
	SDL_Color color = { 32,90,67 };
	std::string title{ "Score: " + std::to_string(score - 3) };
	SDL_Surface* sur = TTF_RenderText_Solid(font, title.c_str(), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, sur);
	int w, h;
	TTF_SizeText(font, title.c_str(), &w, &h);
	SDL_Rect rect = { 40,10,w,h };

	SDL_RenderCopy(renderer, tex, NULL, &rect);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(sur);
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

}


void startGame(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Event e)
{
	string name;
	name = getName(window, renderer);
	TTF_Font* font = nullptr;
	font = TTF_OpenFont("dlx.ttf", 24);
	SDL_Surface* img;
	SDL_Texture* apple;
	img = IMG_Load("apple.png");
	apple = SDL_CreateTextureFromSurface(renderer, img);
	img = IMG_Load("background.png");
	SDL_Texture* bkground = SDL_CreateTextureFromSurface(renderer, img);
	SDL_FreeSurface(img);
	int speed = 200;
	int score = 3;
	Snake snake;
	SDL_Rect food;
	food.w = 30;
	food.h = 30;
	food.x = 10 + (rand() % (780 / 30) * 30);
	food.y = 40 + (rand() % (540 / 30) * 30);
	snake.loadImage(renderer);
	bool running = true;
	while (running)
	{

		FillBackground(renderer, bkground);

		snake.ShowSnake(renderer, score);
		DropFood(renderer, food, apple);
		UpdateScore(renderer, score, font);
		SDL_Delay(speed);

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
				SDL_DestroyTexture(apple);
				SDL_DestroyTexture(bkground);
				snake.destroyTexture();
				TTF_CloseFont(font);
				quitSDL(window, renderer);
			}
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					running = false;
					SDL_DestroyTexture(apple);
					SDL_DestroyTexture(bkground);
					snake.destroyTexture();
					TTF_CloseFont(font);
					quitSDL(window, renderer);
				}
				else
				{
					if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_UP)
					{
						snake.setDirection(0, -1);

					}
					else
						if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN)
						{
							snake.setDirection(0, 1);

						}
						else
							if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT)
							{
								snake.setDirection(-1, 0);

							}
							else
								if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT)
								{
									snake.setDirection(1, 0);

								}
								else
									if (e.key.keysym.sym == SDLK_p)
									{
										pauseMenu(renderer);
									}
				}

			}
		}

		snake.move();
		if (snake.isEat(food))
		{
			score++;
			food.x = 10 + (rand() % (780 / 30) * 30);
			food.y = 40 + (rand() % (540 / 30) * 30);
			while (snake.isSimilar(food))
			{
				food.x = 10 + (rand() % (780 / 30) * 30);
				food.y = 40 + (rand() % (540 / 30) * 30);
			}
			DropFood(renderer, food, apple);
			speed = speed - 3;
		}
		else
			snake.erase();
		if (snake.isHitBox() == 1)
		{
			snake.reset();
			running = false;
		}
		if ((snake.isBitItself() == 1))
		{
			snake.reset();
			running = false;
		}

	}
	SDL_DestroyTexture(apple);
	SDL_DestroyTexture(bkground);
	snake.destroyTexture();
	endMenu(renderer, name, score);
}