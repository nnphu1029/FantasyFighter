#include "pause.h"

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
    if(PauseMenuState == 1){
        MenuButtonFrame = min(MenuButtonFrame + 3,BUTTONFRAME - 1);
    }
    else{
        MenuButtonFrame = FRAMERESET;
    }
    if(PauseMenuState == 2){
        QuitGameButtonFrame = min(QuitGameButtonFrame + 3,BUTTONFRAME - 1);
    }
    else{
        QuitGameButtonFrame = FRAMERESET;
    }
    ResumeButton.render(PauseButton[0].x,PauseButton[0].y,0,ResumeButtonFrame*60,250,60,0);

    MenuButton.render(PauseButton[1].x,PauseButton[1].y,0,MenuButtonFrame*60,250,60,0);

    QuitGameButton.render(PauseButton[2].x,PauseButton[2].y,0,QuitGameButtonFrame*60,250,60,0);
    if(CheckPause == false){
        closePause();
    }
}
void closePause(){
    SDL_DestroyTexture(PauseTexture);
    PauseTexture = NULL;
    QuitGameButton.deleteObject(0);
    ResumeButton.deleteObject(0);
    MenuButton.deleteObject(0);
}
