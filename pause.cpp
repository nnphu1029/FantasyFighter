#include "pause.h"

Object QuitGameButton(0);
Object ResumeButton(0);
Object MenuButton(0);
SDL_Texture* PauseTexture = NULL;
bool CheckPause = false;
int PauseMenuState = 0;
int QuitGameButtonFrame = FRAMERESET;
int ResumeButtonFrame = FRAMERESET;
int MenuButtonFrame = FRAMERESET;

void initPause(){
    PauseTexture = loadTexture("image/PAUSE_menu.png");
    if(PauseTexture == NULL){
        cout << "Load Texture Failed: " << "image/PAUSE_menu.png" << endl;
        return;
    }

    if(!QuitGameButton.loadFromFile("image/QuitGameButton.png")){
        cout << "Could not load:" << "image/QuitGameButton.png" << endl;
        return;
    }
    if(!ResumeButton.loadFromFile("image/ResumeButton.png")){
        cout << "Could not load: " << "image/ResumeButton.png" << endl;
        return;
    }
    if(!MenuButton.loadFromFile("image/MenuButton.png")){
        cout << "Could not load: " << "image/MenuButton.png" << endl;
        return;
    }
}
void renderPause(){
    if(PauseTexture == NULL){
        initPause();
    }
    SDL_RenderCopy(gRenderer,PauseTexture,NULL,NULL);
    if(PauseMenuState == 0){
        ResumeButtonFrame = min(ResumeButtonFrame + 3,BUTTONFRAME - 1);
    }
    else{
        ResumeButtonFrame = FRAMERESET;
    }
    ResumeButton.render(PauseButton[0].x,PauseButton[0].y,0,ResumeButtonFrame*60,250,60,0);

    if(currentState == MAINGAME){
        PauseMenuState = PauseMenuState % 3;

        if(PauseMenuState == 1){
            MenuButtonFrame = min(MenuButtonFrame + 3,BUTTONFRAME - 1);
        }
        else{
            MenuButtonFrame = FRAMERESET;
        }
        MenuButton.render(PauseButton[1].x,PauseButton[1].y,0,MenuButtonFrame*60,250,60,0);

        if(PauseMenuState == 2){
            QuitGameButtonFrame = min(QuitGameButtonFrame + 3,BUTTONFRAME - 1);
        }
        else{
            QuitGameButtonFrame = FRAMERESET;
        }
        QuitGameButton.render(PauseButton[2].x,PauseButton[2].y,0,QuitGameButtonFrame*60,250,60,0);
    }
    else{
        PauseMenuState = PauseMenuState%2;

        if(PauseMenuState == 1){
            QuitGameButtonFrame = min(QuitGameButtonFrame + 3,BUTTONFRAME - 1);
        }
        else{
            QuitGameButtonFrame = FRAMERESET;
        }
        QuitGameButton.render(PauseButton[1].x,PauseButton[1].y,0,QuitGameButtonFrame*60,250,60,0);
    }

    if(CheckPause == false){
        closePause();
    }
    return;
}

void PauseKeyPressProcess(bool &quit){
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
                    CheckPause = false; break;
                case 1:
                    currentState = MENU;
                    quit = true;
                    CheckPause = false; break;
                case 2:
                    quit = true;
                    CheckPause = false;
                    quitFantasyFighter = true; break;
            }
            break;
    }
    return;
}

void closePause(){
    SDL_DestroyTexture(PauseTexture);
    PauseTexture = NULL;
    QuitGameButton.deleteObject(0);
    ResumeButton.deleteObject(0);
    MenuButton.deleteObject(0);
    return;
}
