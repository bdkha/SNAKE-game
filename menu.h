#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <fstream>
#include "game.h"
using namespace std;
void intro(SDL_Renderer* renderer);
void startMenu(SDL_Renderer* renderer);
void endMenu(SDL_Renderer* renderer, string name, int score);
void pauseMenu(SDL_Renderer* renderer);
string getName(SDL_Window* window, SDL_Renderer* renderer);
#endif // !MENU_H


