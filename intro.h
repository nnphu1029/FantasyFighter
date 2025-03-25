#ifndef INTRO_H
#define INTRO_H

#include "const.h"
#include "Object.h"
#include "Interact.h"
#include "init.h"
using namespace std;

extern bool check;
extern SDL_Event FantasyFighter;
extern bool quitFantasyFighter;
extern int currentState;

extern SDL_Texture* introTexture;

void renderIntro();

void closeIntro();

#endif // INTRO_H

