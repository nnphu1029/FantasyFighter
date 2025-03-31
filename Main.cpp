#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>

#include "const.h"
#include "init.h"

#include "intro.h"
#include "opening.h"
#include "menu.h"
#include "game.h"
using namespace std;
bool check = false;

SDL_Window* window = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
SDL_Texture* introTexture = NULL;
SDL_Texture* PauseTexture = NULL;
//HP BAR AND SYMBOL
SDL_Texture* P1_HpBar = NULL;
SDL_Texture* P2_HpBar = NULL;
SDL_Texture* P1_SelectHero = NULL;
SDL_Texture* P2_SelectHero = NULL;

SDL_Event FantasyFighter;

bool quitFantasyFighter = false;

Object openingTheme(0);
Object startButton(0);
Object player1(1);
Object player2(2);
Object P1_Symbol(0);
Object P2_Symbol(0);

Object QuitGameButton(0);
Object ResumeButton(0);
Object MenuButton(0);

int orderRender = 1;
int currentState = INTRO;
int PauseMenuState = 0;
int QuitGameButtonFrame = FRAMERESET;
int ResumeButtonFrame = FRAMERESET;
int MenuButtonFrame = FRAMERESET;
bool CheckPause = false;


int main(int argc, char* args[]){
    Init();
    if(check == false){
        cout << "INIT Failed" << endl;
        return 0;
    }
    while(!quitFantasyFighter){
        while(SDL_PollEvent(&FantasyFighter)){
            if(FantasyFighter.type == SDL_QUIT){
                quitFantasyFighter = true;
            }
        }
        cout << currentState << endl;
        switch(currentState){
            case INTRO:
                renderIntro();
                break;
            case MENU:
                RenderMenu();
                break;
            case MAINGAME:
                mainGame();
                break;
            case EXIT:
                break;
        }
    }
    EndGame();
    return 0;
}





