#ifndef VICTORY_H
#define VICTORY_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "const.h"
#include "Object.h"

extern SDL_Renderer* gRenderer;
extern SDL_Event FantasyFighter;
extern bool quitFantasyFighter;
extern int currentState;

extern int VictoryMenuState;
extern int Winner;

extern Object QuitGameButton;
extern int QuitGameButtonFrame;

extern Object MenuButton;
extern int MenuButtonFrame;

extern Object P1_Symbol;
extern Object P2_Symbol;

const SDL_Rect VictoryButton[3] = {
    {300,500,250,60} , {650,500,250,60}
};

void initVictory();

void VictoryKeyPressProcess(bool&);

void renderVictory();

void closeVictory();

#endif //VICTORY_H
