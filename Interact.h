#ifndef INTERACT_H
#define INTERACT_H

#include<SDL.h>
#include<string>
#include<iostream>
#include<SDL_image.h>
#include "const.h"
#include "Object.h"
#include "data.h"


extern SDL_Texture* P1_HpBar;
extern SDL_Texture* P2_HpBar;
extern Object player1;
extern Object player2;
extern Object P1_Symbol;
extern Object P2_Symbol;
extern int orderRender;
extern SDL_Texture* presentTexture;
extern SDL_Texture* P1_ava;
extern SDL_Texture* P2_ava;
extern bool CheckPause;

extern int Winner;
extern SDL_Rect WinnerCamera;

void updateZoom();

bool mouseInButton(SDL_Rect);

bool MouseClick(SDL_Rect);

bool checkStateAttack(int);

void interactProcess();

void checkHit();


void renderHPBar(int , int);

void renderAvatar(int);


#endif // INTERACT_H
