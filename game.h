#ifndef GAME_H
#define GAME_H

//CONTAIN MAINGAME FUNCTION

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include "const.h"
#include "Object.h"
#include "Interact.h"
#include "init.h"
#include "Opening.h"
#include "pause.h"
#include "victory.h"

extern SDL_Renderer* gRenderer;
extern SDL_Texture* background_Texture;
extern SDL_Event FantasyFighter;
extern bool quitFantasyFighter;
extern int currentState;

extern int orderRender;

extern SDL_Texture* P1_HpBar;
extern SDL_Texture* P2_HpBar;
extern SDL_Texture* P1_ava;
extern SDL_Texture* P2_ava;
extern Object player1;
extern Object player2;
extern Object P1_Symbol;
extern Object P2_Symbol;
extern int currentFrameTime, frameTime;
extern Mix_Chunk* button;
extern int Winner;

extern bool CheckPause;
extern int PauseMenuState;

//Set up 2 players's info: LOCATION, AVATAR, SPRITE,...
void loadingPlayer();
void updateLimit();

//RENDER HP BAR , SYMBOL , AVATAR , ZOOM,  AFTER INTERACT PROCESS
void updateDetails();


//KEYPRESS PROCESS IN MAINGAME
void mainGameKeyPressProcess();

//MAINGAME
void mainGame();

//FREE MAINGAME RESOURCES
void closeMainGame();

#endif // GAME_H
