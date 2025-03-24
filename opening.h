#ifndef OPENING_H
#define OPENING_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "const.h"
#include "init.h"
#include "Object.h"

extern int currentFrameTime , frameTime;
extern SDL_Event FantasyFighter;
extern bool quitFantasyFighter;
extern int currentState;

void renderOpening();

void closeOpening();

#endif

