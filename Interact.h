#ifndef INTERACT_H
#define INTERACT_H

#include<SDL.h>
#include<string>
#include<iostream>
#include<SDL_image.h>
#include "const.h"
#include "Object.h"
#define fi first
#define se second

extern Object player1;
extern Object player2;
extern int orderRender;
extern SDL_Texture* P1_HpBar;
extern SDL_Texture* P2_HpBar;

void interactProcess();
void renderHPBar(int , int);



#endif // INTERACT_H
