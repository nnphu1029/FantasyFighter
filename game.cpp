#include "game.h"

void initPlayer(){
//  LOADING BACKGROUND
    gTexture = loadTexture("image/Bleachst1.png");
    if(gTexture == NULL){
        cout << "Texture Failed" << endl;
        return;
    }
// LOADING PLAYER1
    P1_HpBar = loadTexture("image/player1_health_bar.png");
    if(P1_HpBar == NULL){
        cout << "Could not load image: " << "image/player1_health_bar.png" << endl;
        return;
    }
    if(!player1.loadFromFile(HeroData[player1.heroCode].filename)){
        cout << "Could not load player1:" << HeroData[player1.heroCode].filename << endl;
        return;
    }
    if(!P1_Symbol.loadFromFile("image/P1_icon.png")){
        cout << "Could not load image: " << "image/P1_icon.png" << endl;
        return;
    }

//  LOADING PLAYER2
    P2_HpBar = loadTexture("image/player2_health_bar.png");
    if(P2_HpBar == NULL){
        cout << "Could not load image: " << "image/player2_health_bar.png" << endl;
        return;
    }
    if(!player2.loadFromFile(HeroData[player2.heroCode].filename)){
        cout << "Could not load player2:" << HeroData[player2.heroCode].filename << endl;
        return;
    }
    if(!P2_Symbol.loadFromFile("image/P2_icon.png")){
        cout << "Could not load image: " << "image/P2_icon.png" << endl;
        return;
    }
}

void mainGame(){
    initPlayer();
    updateLimit();

    int currentFrameTime, frameTime;
    bool quitGame = false;
    while(!quitGame){
        currentFrameTime = SDL_GetTicks();
        SDL_RenderCopy(gRenderer,gTexture,NULL,NULL);
        while(SDL_PollEvent(&FantasyFighter) != 0){
            if(FantasyFighter.type == SDL_QUIT){
                quitGame = true;
                quitFantasyFighter = true;
                continue;
            }
            if(FantasyFighter.type == SDL_KEYDOWN){
                switch (FantasyFighter.key.keysym.sym){
                    case(SDLK_j):
                        player1.Attack();
                        break;
                    case(SDLK_w):
                        player1.Jump();
                        break;
                    case(SDLK_l):
                        player1.Dash();
                        break;
                    case(SDLK_s):
                        player1.Block();
                        break;
                    case(SDLK_u):
                        player1.SpecAttack();
                        break;

                    case(SDLK_KP_4):
                        player2.Attack();
                        break;
                    case(SDLK_UP):
                        player2.Jump();
                        break;
                    case(SDLK_KP_6):
                        player2.Dash();
                        break;
                    case(SDLK_DOWN):
                        player2.Block();
                        break;
                    case (SDLK_KP_7):
                        player2.SpecAttack();
                        break;

                    case SDLK_ESCAPE:
                        quitGame = true;
                        quitFantasyFighter = true;
                        break;
                    case SDLK_t:
                        player1.HP = 0;
                        player2.HP = 0;
//                        quitGame = true;
//                        currentState = INTRO;
                        break;
                }
            }
        }
        //UPDATE CHARACTER
        player1.objectFlag = SDL_GetKeyboardState(NULL);
        player2.objectFlag = SDL_GetKeyboardState(NULL);
//        cout << player1.Status << " " << player2.Status << endl;
        if(orderRender == 1){
            player1.movementUpdate(HeroData[player1.heroCode].frWidth , HeroData[player1.heroCode].frHeight , 1);
            player2.movementUpdate(HeroData[player2.heroCode].frWidth , HeroData[player2.heroCode].frHeight , 2);
        }
        else{
            player2.movementUpdate(HeroData[player2.heroCode].frWidth , HeroData[player2.heroCode].frHeight , 2);
            player1.movementUpdate(HeroData[player1.heroCode].frWidth , HeroData[player1.heroCode].frHeight , 1);
        }

        interactProcess();

    // PRESENT RENDERER
        SDL_RenderPresent(gRenderer);
    // MANAGE FPS
        frameTime = SDL_GetTicks() - currentFrameTime;
        if (frameTime < TARGET_FRAME_TIME) {
            SDL_Delay(TARGET_FRAME_TIME - frameTime);
        }
    }
    closeMainGame();
    return;
}

void updateLimit(){
    player1.limitP1 = 12 -  (HeroData[player1.heroCode].frWidth/2);
    player1.limitP2 = scrWidth - (13 +  (HeroData[player1.heroCode].frWidth/2));
    player2.limitP1 = 12 -  (HeroData[player2.heroCode].frWidth/2);
    player2.limitP2 = scrWidth - (13 +  (HeroData[player2.heroCode].frWidth/2));
}

void closeMainGame(){
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
    SDL_DestroyTexture(P1_HpBar);
    P1_HpBar = NULL;
    SDL_DestroyTexture(P2_HpBar);
    P2_HpBar = NULL;
    player1.deleteObject(1);
    player2.deleteObject(2);
    P1_Symbol.deleteObject(0);
    P2_Symbol.deleteObject(0);
}
