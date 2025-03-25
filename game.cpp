#include "game.h"

void mainGame(){
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

                    case(SDLK_KP_4):
                        player2.Attack();
                        break;
                    case(SDLK_UP):
                        player2.Jump();
                        break;
                    case(SDLK_KP_6):
                        player2.Dash();
                        break;
                    case SDLK_ESCAPE:
                        quitGame = true;
                        quitFantasyFighter = true;
                        break;
                }
            }
        }
        //UPDATE CHARACTER
        player1.objectFlag = SDL_GetKeyboardState(NULL);
        player2.objectFlag = SDL_GetKeyboardState(NULL);

        if(orderRender == 1){
            player1.movementUpdate(FRAME_SIZE , FRAME_SIZE , 1);
            player2.movementUpdate(FRAME_SIZE , FRAME_SIZE , 2);
        }
        else{
            player2.movementUpdate(FRAME_SIZE , FRAME_SIZE , 2);
            player1.movementUpdate(FRAME_SIZE , FRAME_SIZE , 1);
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

void closeMainGame(){
    if(gTexture != NULL){
        SDL_DestroyTexture(gTexture);
        gTexture = NULL;
    }
    if(P1_HpBar != NULL){
        SDL_DestroyTexture(P1_HpBar);
        P1_HpBar = NULL;
    }
    if(P2_HpBar != NULL){
        SDL_DestroyTexture(P2_HpBar);
        P2_HpBar = NULL;
    }
    player1.deleteObject();
    player2.deleteObject();

    P1_Symbol.deleteObject();
    P2_Symbol.deleteObject();
}
