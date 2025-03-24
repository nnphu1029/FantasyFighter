#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "const.h"
#include "opening.h"

extern Object openingTheme;

void renderOpening(){
    bool quitOpening = false;
    int Oframe = FRAMERESET;
    while(!quitOpening){
        currentFrameTime = SDL_GetTicks();
        while(SDL_PollEvent(&FantasyFighter)){
            if(FantasyFighter.type == SDL_QUIT){
                quitOpening = true;
                quitFantasyFighter = true;
                continue;
            }
            if(FantasyFighter.type == SDL_KEYDOWN){
                switch (FantasyFighter.key.keysym.sym){
                    case SDLK_ESCAPE:
                        quitOpening = true;
                        quitFantasyFighter = true;
                        break;
                }
            }
        }
        if(Oframe == OPENINGFRAME){
            quitOpening = true;
            currentState = MAINGAME;
            continue;
        }
        Oframe += 1;
        openingTheme.render(0 , 0 , 0 , 300*Oframe , 600 , 300  , 3);
        SDL_RenderPresent(gRenderer);
        frameTime = SDL_GetTicks() - currentFrameTime;
        if (frameTime < TARGET_FRAME_TIME) {
            SDL_Delay(TARGET_FRAME_TIME - frameTime);
        }
    }
    closeOpening();
    return;
}
void closeOpening(){
    openingTheme.deleteObject();
}

