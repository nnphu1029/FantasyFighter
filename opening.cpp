#include "opening.h"


void renderOpening(){
    if(!openingTheme.loadFromFile("image/OPENINGFF.png")){
            cout << "Could not load opening theme:" << "image/OPENINGFF.png" << endl;
            return;
    }
    int currentFrameTime , frameTime;
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
        }
        if(Oframe == OPENINGFRAME){
            quitOpening = true;
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
    if(quitFantasyFighter == true){
        EndGame();
        SDL_Quit();
    }
    return;
}
void closeOpening(){
    openingTheme.deleteObject(0);
}

