#include "intro.h"

void renderIntro(){
    introTexture = loadTexture("image/intro.png");
    if(introTexture == NULL){
        cout << "Loading Intro FAILED: " << "image/intro.png";
        return;
    }
    bool quitIntro = false;
    int currentFrameTime, frameTime;
    while(!quitIntro){
         currentFrameTime = SDL_GetTicks();
         while(SDL_PollEvent(&FantasyFighter) != 0){
            if(FantasyFighter.type == SDL_QUIT){
                quitIntro = true;
                quitFantasyFighter = true;
                continue;
            }
            if(FantasyFighter.type == SDL_KEYDOWN){
                switch (FantasyFighter.key.keysym.sym){
                    case SDLK_ESCAPE:
                        quitIntro = true;
                        quitFantasyFighter = true;
                        break;
                    case SDLK_RETURN:
                        quitIntro = true;
                        break;

                }
            }
         }
         if(quitIntro == true){
            currentState = OPENING;
            continue;
         }
         SDL_RenderCopy(gRenderer,introTexture,NULL,NULL);
         SDL_RenderPresent(gRenderer);
         frameTime = SDL_GetTicks() - currentFrameTime;
        if (frameTime < TARGET_FRAME_TIME) {
            SDL_Delay(TARGET_FRAME_TIME - frameTime);
        }
    }
    closeIntro();
    return;
}
void closeIntro(){
    if(introTexture == NULL){
        SDL_DestroyTexture(introTexture);
        introTexture = NULL;
    }
}
