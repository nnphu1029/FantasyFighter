#ifndef INIT_H
#define INIT_H

// SET UP SDL2, LOADING WINDOW FUNCTION, LOADING SPRITE FUNCTION, ENDGAME FUNCTION

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include "const.h"
#include "Object.h"
#include "data.h"
using namespace std;

extern bool check;
extern SDL_Renderer* gRenderer;
extern SDL_Window* window;
extern SDL_Texture* background_Texture;
extern SDL_Texture* introTexture;
extern SDL_Texture* P1_HpBar;
extern SDL_Texture* P2_HpBar;
extern SDL_Texture* P1_SelectHero;
extern SDL_Texture* P2_SelectHero;
extern SDL_Texture* PauseTexture;
extern Object QuitGameButton;
extern Object MenuButton;
extern Object ResumeButton;
extern Object player1;
extern Object player2;
extern Object P1_Symbol;
extern Object P2_Symbol;
extern Mix_Chunk* button;
//SET UP WINDOW, IMAGE AND SOUND
void Init();

//LOADING SPRITE FUNCTION
SDL_Texture* loadTexture(string path);

//DELETE GAME RESOURCES
void EndGame();

#endif // INIT_H
