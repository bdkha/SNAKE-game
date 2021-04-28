#include "menu.h"

void intro(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 19, 17, 17, 0);
	SDL_RenderClear(renderer);
	SDL_Surface* img;
	SDL_Texture* texture;
	img = IMG_Load("ti.png");
	texture = SDL_CreateTextureFromSurface(renderer, img);
	SDL_Rect dsrect = { 290,239,232,249 };
	SDL_RenderCopy(renderer, texture, NULL, &dsrect);
	SDL_RenderPresent(renderer);
	SDL_Delay(500);
	for (int i = 239; i > 55; i = i - 6)
	{
		dsrect.y = i;
		SDL_RenderCopy(renderer, texture, NULL, &dsrect);
		SDL_RenderPresent(renderer);
		SDL_Delay(30);
		SDL_SetRenderDrawColor(renderer, 19, 17, 17, 0);
		SDL_RenderClear(renderer);
	}
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(img);
}
void startMenu(SDL_Renderer* renderer)
{
	SDL_Surface* img;
	SDL_Texture* texture;
	img = IMG_Load("startmenu.png");
	texture = SDL_CreateTextureFromSurface(renderer, img);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(img);
}
void pauseMenu(SDL_Renderer* renderer)
{
	SDL_Surface* img;
	SDL_Texture* texture;
	img = IMG_Load("pausemenu.png");
	texture = SDL_CreateTextureFromSurface(renderer, img);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(img);
	SDL_Event e;
	while (true)
	{
		if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
			return;
		SDL_Delay(100);
	}
}
string getName(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_Surface* img = IMG_Load("name.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_FreeSurface(img);
	TTF_Font* font = TTF_OpenFont("dlx.ttf", 40);
	SDL_Surface* surface = NULL;
	SDL_Texture* text = NULL;
	int w, h;
	SDL_Rect rect;
	SDL_Event e;
	string s;
	SDL_Color cl = { 237,37,44 };
	while (true)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				SDL_FreeSurface(surface);
				SDL_DestroyTexture(text);
				quitSDL(window, renderer);
			}
			else
				if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_ESCAPE)
					{
						SDL_FreeSurface(surface);
						SDL_DestroyTexture(text);
						quitSDL(window, renderer);
					}
					else
						if (e.key.keysym.sym == SDLK_RETURN)
						{
							SDL_FreeSurface(surface);
							SDL_DestroyTexture(text);
							return s;
						}
					if (e.key.keysym.sym == SDLK_BACKSPACE)
					{
						if (s.length() > 0)
							s.pop_back();
					}
					else
					{
						s = s + static_cast<char>((int)e.key.keysym.sym);
					}
				}
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			surface = TTF_RenderText_Solid(font, s.c_str(), cl);
			text = SDL_CreateTextureFromSurface(renderer, surface);
			TTF_SizeText(font, s.c_str(), &w, &h);
			rect = { 420 - 24 * (int)s.length(),221,w,h };
			SDL_RenderCopy(renderer, text, NULL, &rect);
			SDL_RenderPresent(renderer);
			SDL_Delay(50);
		}
	}

}
void endMenu(SDL_Renderer* renderer, string name, int score)
{
	// update score
	fstream fsFile;
	fsFile.open("highscore.txt", ios::in);
	struct loop
	{
		string name;
		int score;
	};
	struct loop a;
	fsFile >> a.name >> a.score;
	fsFile.close();
	if (score > a.score)
	{
		a.name = name;
		a.score = score;
	}
	fsFile.open("highscore.txt", ios::out);
	fsFile << a.name << " " << a.score;
	fsFile.close();
	//draw end menu
	TTF_Font* font = TTF_OpenFont("dlx.ttf", 46);
	SDL_Surface* surface;
	SDL_Texture* texture;
	surface = IMG_Load("endmenu.png");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, NULL);

	SDL_Color color = { 244,67,54 };
	string text = std::to_string(score - 3);
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	int w, h;
	TTF_SizeText(font, text.c_str(), &w, &h);
	SDL_Rect rect = { 215,213,w,h };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_RenderPresent(renderer);

	text = name;
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	TTF_SizeText(font, text.c_str(), &w, &h);
	rect = { 410,213,w,h };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_RenderPresent(renderer);

	color = { 253,191,7 };
	text = std::to_string(a.score - 3);
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	TTF_SizeText(font, text.c_str(), &w, &h);
	rect = { 215,325,w,h };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_RenderPresent(renderer);

	text = a.name;
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	TTF_SizeText(font, text.c_str(), &w, &h);
	rect = { 410,325,w,h };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}