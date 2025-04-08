#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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

int currentFrameTime, frameTime;
SDL_Event FantasyFighter;
bool quitFantasyFighter = false;
int currentState = INTRO;


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
        if(quitFantasyFighter == true){
            EndGame();
            continue;
        }
        switch(currentState){
            case INTRO:
                renderIntro();
                if(quitFantasyFighter == true){
                    EndGame();
                }
                break;
            case MENU:
                RenderMenu();
                if(quitFantasyFighter == true){
                    EndGame();
                }
                break;
            case MAINGAME:
                mainGame();
                if(quitFantasyFighter == true){
                    EndGame();
                }
                break;
        }
    }
    EndGame();
    return 0;
}





