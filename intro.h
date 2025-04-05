#ifndef INTRO_H
#define INTRO_H

#include "const.h"
#include "Object.h"
#include "Interact.h"
#include "init.h"
#include "Opening.h"
#include "pause.h"
using namespace std;

extern SDL_Event FantasyFighter;
extern bool quitFantasyFighter;
extern int currentState;
extern int currentFrameTime, frameTime;

extern Object startButton;

extern SDL_Texture* introTexture;

extern bool CheckPause;
extern int PauseMenuState;

void initIntro();

void renderIntro();

void closeIntro();

#endif // INTRO_H

