#ifndef INTERACT_H
#define INTERACT_H

#include<SDL.h>
#include<string>
#include<iostream>
#include<SDL_image.h>
#include "const.h"
#include "Object.h"
#include "data.h"
#define fi first
#define se second


extern SDL_Texture* P1_HpBar;
extern SDL_Texture* P2_HpBar;
extern Object player1;
extern Object player2;
extern Object P1_Symbol;
extern Object P2_Symbol;
extern int orderRender;

bool mouseInButton(SDL_Rect);

bool MouseClick(SDL_Rect);

bool checkStateAttack(int);

void interactProcess();

void checkHit();

void renderHPBar(int , int);



#endif // INTERACT_H
