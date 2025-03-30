#ifndef INIT_H
#define INIT_H

#include<SDL.h>
#include<iostream>
#include<SDL_image.h>
#include "const.h"
#include "Object.h"
#include "data.h"
using namespace std;

extern bool check;
extern SDL_Renderer* gRenderer;
extern SDL_Window* window;
extern SDL_Texture* gTexture;
extern SDL_Texture* introTexture;
extern SDL_Texture* P1_HpBar;
extern SDL_Texture* P2_HpBar;
extern SDL_Texture* P1_SelectHero;
extern SDL_Texture* P2_SelectHero;
extern Object player1;
extern Object player2;
extern Object P1_Symbol;
extern Object P2_Symbol;

void Init();
void EndGame();
void loadMedia();
SDL_Texture* loadTexture(string path);

#endif // INIT_H
