#ifndef GAME_H
#define GAME_H


#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <ctime>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;


SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string file_path);
void startGame(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Event e);
void FillBackground(SDL_Renderer* renderer, SDL_Texture* background);
void DropFood(SDL_Renderer* renderer, SDL_Rect rectangle, SDL_Texture* apple);
void UpdateScore(SDL_Renderer* renderer, int score, TTF_Font* font);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
class Snake
{
private:
	const int sizeSquare = 30;
	struct Node
	{

		int x;
		int y;
		int direct;
		int tail;
		Node* next;
	};
	int len = 0;// do dai cua ran
	int tempx = 10, tempy = 40;
	Node* head = new Node;
	Node* finish = new Node;
	int headdirect, direct;
	int LorR, UorD;
	SDL_Texture* pictures[15];
	//load anh ran

public:
	Snake()
	{
		//khoi tao ran ban dau
		headdirect = 1;
		tempx = 10;
		tempy = 40;
		head->x = tempx;
		head->y = tempy;
		head->direct = headdirect;
		head->tail = headdirect;
		head->next = NULL;
		finish = head;
		len++;
		//****************
		tempx = 40;
		tempy = 40;
		push(tempx, tempy, headdirect, headdirect, head);
		//****************
		tempx = 70;
		tempy = 40;
		push(tempx, tempy, headdirect, headdirect, finish);
		//hướng di chuyển
		UorD = 0;
		LorR = 1;
	}
	void push(int x, int y, int direct, int tail, Node* last)
	{
		Node* newNode = new Node;
		newNode->x = x;
		newNode->y = y;
		newNode->direct = direct;
		newNode->tail = tail;
		newNode->next = NULL;
		last->next = newNode;
		finish = newNode;
		len++;
	}
	void erase()
	{
		Node* old = head;
		head = head->next;
		delete old;
		len--;
	}

	//giai phong anh ran
	void destroyTexture()
	{
		for (int i = 1; i < 15; i++)
		{
			SDL_DestroyTexture(pictures[i]);
		}
	}
	//load anh ran
	void loadImage(SDL_Renderer* renderer)
	{
		pictures[1] = loadTexture(renderer, "snakehead1.png");
		pictures[2] = loadTexture(renderer, "snakehead2.png");
		pictures[3] = loadTexture(renderer, "snakehead3.png");
		pictures[4] = loadTexture(renderer, "snakehead4.png");
		pictures[5] = loadTexture(renderer, "snake_veritical.png");
		pictures[6] = loadTexture(renderer, "snake_horizontal.png");
		pictures[7] = loadTexture(renderer, "snake1.png");
		pictures[8] = loadTexture(renderer, "snake2.png");
		pictures[9] = loadTexture(renderer, "snake3.png");
		pictures[10] = loadTexture(renderer, "snake4.png");
		pictures[11] = loadTexture(renderer, "snaketail1.png");
		pictures[12] = loadTexture(renderer, "snaketail2.png");
		pictures[13] = loadTexture(renderer, "snaketail3.png");
		pictures[14] = loadTexture(renderer, "snaketail4.png");

	}
	// check xem rắn đã ăn mồi chưa
	bool isEat(SDL_Rect food)
	{
		if (food.x == tempx && food.y == tempy)
		{
			return 1;//Ate
		}
		return 0;//not eat
	}
	// check xem food có bị trùng với thân rắn không?
	bool isSimilar(SDL_Rect food)
	{
		bool kt = 0;
		for (Node* p = head; p != NULL; p = p->next)
		{
			if (food.x == p->x && food.y == p->y)
			{
				kt = 1;
				break;
			}
		}
		return kt;
	}
	bool isHitBox()
	{
		if (finish->x == -20 || finish->x == 790)
			return 1;
		else
			if (finish->y == 10 || finish->y == 580)
				return 1;
			else
				return 0;
	}
	//check xem rắn có tự cắn mình không?
	bool isBitItself()
	{
		bool kt = 0;
		int i = 1;
		Node* p;
		for (p = head; p != NULL; p = p->next)
		{
			if (i < len - 2)
			{
				if (tempx == p->x && tempy == p->y)
				{
					kt = 1;
					break;
				}
			}
			i++;
		}
		return kt;
	}
	void setDirection(int a, int b)
	{
		if ((LorR * a) != -1)
			LorR = a;
		if ((UorD * b) != -1)
			UorD = b;
		if (LorR == 1 && UorD == 0)
		{
			if (headdirect == 2)
				finish->direct = 10;
			else
				if (headdirect == 4)
					finish->direct = 7;
			headdirect = 1;
		}

		else

			if (LorR == 0 && UorD == 1)
			{
				if (headdirect == 1)
					finish->direct = 8;
				else
					if (headdirect == 3)
						finish->direct = 7;
				headdirect = 2;
			}

			else
				if (LorR == -1 && UorD == 0)
				{
					if (headdirect == 2)
						finish->direct = 9;
					else
						if (headdirect == 4)
							finish->direct = 8;
					headdirect = 3;
				}
				else
				{
					if (headdirect == 1)
						finish->direct = 9;
					else
						if (headdirect == 3)
							finish->direct = 10;
					headdirect = 4;
				}
	}
	//trả về giá trị của hướng trái hay phải
	int getLorR()
	{
		return LorR;
	}

	//trả về giá trị của hướng trên hay dưới
	int getUorD()
	{
		return UorD;
	}
	//tăng chiều dài rắn
	// di chuyển
	void move()
	{
		switch (LorR)
		{
		case 0:
			tempy += sizeSquare * UorD;
			break;
		case -1: case 1:
			tempx += sizeSquare * LorR;
			break;
		}

		push(tempx, tempy, headdirect, headdirect, finish);
	}
	//vẽ rắn
	void ShowSnake(SDL_Renderer* renderer, int score)
	{

		Node* p;
		int i = 0;
		SDL_Rect square;
		for (p = head; p != NULL; p = p->next)
		{
			i++;
			square = { p->x,p->y,sizeSquare,sizeSquare };
			if (i == 1)
				SDL_RenderCopy(renderer, pictures[p->next->tail + 10], NULL, &square);// ve duoi
			else
			{
				if (i == len)
					SDL_RenderCopy(renderer, pictures[finish->direct], NULL, &square);//ve dau
				else
				{
					if (p->direct > 6)
						SDL_RenderCopy(renderer, pictures[p->direct], NULL, &square);//
					else                                                             //
					{                                                                //
						if (p->direct % 2 == 0)                                      //ve than
							SDL_RenderCopy(renderer, pictures[5], NULL, &square);    //
						else                                                         //
							if (p->direct % 2 != 0)                                  //
								SDL_RenderCopy(renderer, pictures[6], NULL, &square);//
					}
				}
			}

		}
	}
	void reset()
	{
		do
		{
			erase();
		} while (head->next != NULL);
		len = 0;

	}
};
#endif 
