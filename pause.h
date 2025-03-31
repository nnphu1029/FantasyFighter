#ifndef PAUSE_H
#define PAUSE_H

#include<string>
#include<SDL.h>
#include "Object.h"
#include "init.h"
using namespace std;

extern bool quitFantasyFighter;
extern int currentState;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* PauseTexture;

extern Object QuitGameButton;
extern Object MenuButton;
extern Object ResumeButton;

extern bool CheckPause;
extern int QuitGameButtonFrame;
extern int ResumeButtonFrame;
extern int MenuButtonFrame;
extern int PauseMenuState;

const SDL_Rect PauseButton[3] = {
    {470,225,250,60} , {470,290,250,60} ,  {470,355,250,60}
};


void initPause();
void renderPause();
void closePause();

#endif // PAUSE_H
