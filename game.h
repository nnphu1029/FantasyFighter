#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
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

extern int Winner;

extern bool CheckPause;
extern int PauseMenuState;

void loadingPlayer();

void updateDetails();

void updateLimit();

void mainGameKeyPressProcess();

void mainGame();

void closeMainGame();

#endif // GAME_H
