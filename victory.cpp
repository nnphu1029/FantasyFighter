#include "victory.h"

Object VictorySign(0);
int Winner = -1;
int VictorySignFrame = FRAMERESET;
int VictoryMenuState = 0;


void initVictory(){
    if(!VictorySign.loadFromFile("image/victory.png")){
        cout << "Can not load image: " << "image/victory.png" << endl;
        return;
    }
    VictorySignFrame = FRAMERESET;
    if(!MenuButton.loadFromFile("image/MenuButton.png")){
        cout << "Could not load: " << "image/MenuButton.png" << endl;
        return;
    }
    MenuButtonFrame = FRAMERESET;
    if(!QuitGameButton.loadFromFile("image/QuitGameButton.png")){
        cout << "Could not load:" << "image/QuitGameButton.png" << endl;
        return;
    }
    QuitGameButtonFrame = FRAMERESET;
    return;
}

void VictoryKeyPressProcess(bool &quit){
    switch (FantasyFighter.key.keysym.sym){
        case SDLK_LEFT:
            VictoryMenuState = max(VictoryMenuState - 1,0);
            break;
        case SDLK_RIGHT:
            VictoryMenuState = min(VictoryMenuState + 1,1);
            break;
        case (SDLK_RETURN):
            switch (VictoryMenuState){
                case 0:
                    currentState = MENU;
                    quit = true;
                    Winner = -1;
                    break;
                case 1:
                    quit = true;
                    quitFantasyFighter = true;
                    Winner = -1;
                    break;
            }
            break;
    }
}

void renderVictory(){
    if(VictorySign.getTexture() == NULL){
        initVictory();
    }

    if(Winner == 1){
        P1_Symbol.render(300,200,0,0,100,100,0);
    }
    else{
        P2_Symbol.render(300,200,0,0,100,100,0);
    }
    VictorySignFrame = min(VictorySignFrame + 1,BUTTONFRAME - 1);
    VictorySign.render(400,200,0,VictorySignFrame*100 ,500, 100 ,0);

    if(VictorySignFrame == BUTTONFRAME - 1){
        VictoryMenuState = VictoryMenuState%2;
        if(VictoryMenuState == 0){
            MenuButtonFrame = min(MenuButtonFrame + 2,BUTTONFRAME - 1);
        }
        else{
            MenuButtonFrame = FRAMERESET;
        }
        MenuButton.render(VictoryButton[0].x,VictoryButton[0].y,0,MenuButtonFrame*60,250,60,0);

        if(VictoryMenuState == 1){
            QuitGameButtonFrame = min(QuitGameButtonFrame + 2,BUTTONFRAME - 1);
        }
        else{
            QuitGameButtonFrame = FRAMERESET;
        }
        QuitGameButton.render(VictoryButton[1].x,VictoryButton[1].y,0,QuitGameButtonFrame*60,250,60,0);
    }
    if(Winner == -1){
        closeVictory();
    }
}
void closeVictory(){
    VictorySign.deleteObject(0);
    MenuButton.deleteObject(0);
    QuitGameButton.deleteObject(0);
}


