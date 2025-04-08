#ifndef OPENING_H
#define OPENING_H

//CONTAIN OPENING FUNCTION

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "init.h"
#include "const.h"
#include "Object.h"

extern SDL_Event FantasyFighter;
extern bool quitFantasyFighter;
extern int currentState;
extern Object openingTheme;

//RENDER OPENING
void renderOpening();

//DELETE OPENING RESOURCES
void closeOpening();

#endif

