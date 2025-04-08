#include "intro.h"

Object openingTheme(0);
Object startButton(0);
SDL_Texture* introTexture = NULL;
Mix_Music* introBackGroundMusic;

void initIntro(){
    introTexture = loadTexture("image/intro.png");
    if(introTexture == NULL){
        cout << "Loading Intro FAILED: " << "image/intro.png";
        return;
    }
    if(!startButton.loadFromFile("image/startButton.png")){
        cout << "Could not load start button:" << "image/startButton.png" << endl;
        return;
    }
    introBackGroundMusic = Mix_LoadMUS("sound/intro.ogg");
    if (!introBackGroundMusic) {
        cout << "Could not load Menu music" << endl;
        return;
    }
    else{
        Mix_PlayMusic(introBackGroundMusic, -1);
    }
    return;
}


void renderIntro(){
    initIntro();

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
                Mix_PlayChannel(-1, button, 0);
                if(CheckPause == true){
                    switch (FantasyFighter.key.keysym.sym){
                        case(SDLK_UP):
                            PauseMenuState = max(PauseMenuState - 1,0);
                            break;
                        case(SDLK_DOWN):
                            PauseMenuState = min(PauseMenuState + 1,2);
                            break;
                        case (SDLK_RETURN):
                            switch (PauseMenuState){
                                case 0:
                                    CheckPause = false;
                                    break;
                                case 1:
                                    quitIntro = true;
                                    quitFantasyFighter = true;
                                    CheckPause = false;
                                    break;
                            }
                            break;
                    }
                    break;
                }
                else{
                    switch (FantasyFighter.key.keysym.sym){
                        case SDLK_ESCAPE:
                            CheckPause = true;
                            break;
                        case SDLK_RETURN:
                            currentState = MENU;
                            break;
                    }
                }
            }
        }
        if(CheckPause == true){
            SDL_RenderCopy(gRenderer,introTexture,NULL,NULL);
            startButton.render(450,450,0,buttonFrame*80 ,300, 80,0);
            renderPause();
        }
        else{
            if(buttonFrame == 20 and currentState != INTRO){
                quitIntro = true;
                continue;
            }
            if(currentState == INTRO){
                if(mouseInButton(START)){
                    buttonFrame = 19;
                    if(MouseClick(START)){
                        currentState = MENU;
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
        }

        SDL_RenderPresent(gRenderer);

        frameTime = SDL_GetTicks() - currentFrameTime;
        if (frameTime < TARGET_FRAME_TIME) {
            SDL_Delay(TARGET_FRAME_TIME - frameTime);
        }
    }
    closeIntro();
    if(quitFantasyFighter != true){
        renderOpening();
    }
    return;
}
void closeIntro(){
    Mix_FreeMusic(introBackGroundMusic);
    introBackGroundMusic = NULL;
    SDL_DestroyTexture(introTexture);
    introTexture = NULL;
    startButton.deleteObject(0);
}
