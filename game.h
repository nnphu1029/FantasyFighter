#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "const.h"
#include "Object.h"
#include "Interact.h"


extern SDL_Renderer* gRenderer;
extern SDL_Texture* gTexture;

extern SDL_Texture* P1_HpBar;
extern SDL_Texture* P2_HpBar;

extern Object player1;
extern Object player2;
extern Object P1_Symbol;
extern Object P2_Symbol;


extern int currentFrameTime , frameTime;
extern SDL_Event FantasyFighter;
extern bool quitFantasyFighter;
extern int orderRender;

extern bool check;

void mainGame();

#endif // GAME_H
