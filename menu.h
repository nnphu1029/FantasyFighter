#ifndef MENU_H
#define MENU_H

#include<string>
#include<SDL.h>
#include "Object.h"
#include "init.h"
#include "Opening.h"
#include "pause.h"
using namespace std;


extern SDL_Renderer* gRenderer;
extern SDL_Texture* gTexture;
extern SDL_Texture* P1_SelectHero;
extern SDL_Texture* P2_SelectHero;

extern Object player1;
extern Object player2;

extern SDL_Event FantasyFighter;
extern bool quitFantasyFighter;
extern int currentState;

extern bool CheckPause;
extern int PauseMenuState;

const SDL_Rect menuHero[9] = {
    {155,50,108,125} , {290,50,108,125} , {405,50,108,125},
    {155,190,108,125} , {290,190,108,125} , {405,190,108,125},
    {155,330,108,125} , {290,330,108,125} , {405,330,108,125}
};


void initMenu();
void RenderMenu();
void closeMenu();

#endif // MENU_H





