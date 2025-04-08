#ifndef PAUSE_H
#define PAUSE_H

//CONTAIN PAUSE FUNCTION

#include<string>
#include<SDL.h>
#include "Object.h"
#include "init.h"
using namespace std;

extern bool quitFantasyFighter;
extern int currentState;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* PauseTexture;

extern SDL_Event FantasyFighter;
extern int currentState;

extern bool CheckPause;
extern int PauseMenuState;

const SDL_Rect PauseButton[3] = {
    {470,225,250,60} , {470,290,250,60} ,  {470,355,250,60}
};

//LOADING PAUSE RESOURCES
void initPause();

//KEYPRESS PROCESSING IN PAUSEMENU
void PauseKeyPressProcess(bool&);

//RENDER PAUSE
void renderPause();

//DELETE PAUSE RESOURCES
void closePause();

#endif // PAUSE_H
