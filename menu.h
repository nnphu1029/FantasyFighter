#ifndef MENU_H
#define MENU_H

//CONTAIN MENU FUNCTION

#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include <cstdlib>
#include "Object.h"
#include "init.h"
#include "Opening.h"
#include "pause.h"
#include "const.h"



extern SDL_Renderer* gRenderer;
extern SDL_Texture* background_Texture;

extern Object player1;
extern Object player2;
extern int currentFrameTime, frameTime;

extern SDL_Event FantasyFighter;
extern bool quitFantasyFighter;
extern int currentState;

extern bool CheckPause;
extern int PauseMenuState;


//LOADING MENU RESOURCES
void initMenu();

//RENDER MENU
void RenderMenu();

//LOADING MAP AFTER MENU
void loadingMap(int);

//DELETE MENU RESOURCES
void closeMenu();

#endif // MENU_H





