#ifndef OPENING_H
#define OPENING_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "const.h"
#include "Object.h"

extern SDL_Event FantasyFighter;
extern bool quitFantasyFighter;
extern int currentState;
extern Object openingTheme;

bool checkMouse(int , int , SDL_Rect);

void renderOpening();
void closeOpening();

#endif

