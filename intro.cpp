#include "intro.h"

void loadIntroResource(){
    introTexture = loadTexture("image/intro.png");
    if(introTexture == NULL){
        cout << "Loading Intro FAILED: " << "image/intro.png";
        return;
    }
    if(!startButton.loadFromFile("image/startButton.png")){
        cout << "Could not load start button:" << "image/startButton.png" << endl;
        return;
    }
}


void renderIntro(){
    loadIntroResource();

    int buttonFrame = FRAMERESET;
    bool quitIntro = false;
    int currentFrameTime, frameTime;
    SDL_Rect START = {450,450,startButton.getWidth(),startButton.getHeight()};

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
                        currentState = OPENING;
                        break;
                }
            }
        }
        if(buttonFrame == 20 and currentState != INTRO){
            quitIntro = true;
            continue;
        }
        if(currentState == INTRO){
            if(mouseInButton(START)){
                buttonFrame = 19;
                if(MouseClick(START)){
                    currentState = OPENING;
                    continue;
                }
            }
            else buttonFrame = (buttonFrame + 1)%18;
        }
        else{
            buttonFrame ++;
        }

        SDL_RenderCopy(gRenderer,introTexture,NULL,NULL);
        startButton.render(450,450,0,buttonFrame*80 ,300, 80,0);

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
    startButton.deleteObject();
}
