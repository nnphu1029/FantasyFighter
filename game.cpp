#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "const.h"
#include "init.h"
#include "Object.h"
#include "Interact.h"
#include "game.h"
#define fi first
#define se second

void mainGame(){
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
        if(quitFantasyFighter == true){
            continue;
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

        if(player1.Status == MOVEMENT_ATTACK or player2.Status == MOVEMENT_ATTACK){
            interactProcess();
        }

        P1_Symbol.render(player1.oX + HeroLists[player1.heroCode].body.x,
                         player1.oY + (HeroLists[player1.heroCode].body.y - 26), 0 , 0 ,25,26,0);
        P2_Symbol.render(player2.oX + HeroLists[player2.heroCode].body.x,
                         player2.oY + (HeroLists[player2.heroCode].body.y - 26), 0 , 0 ,25,26,0);
        renderHPBar(100 - player1.HP , 1);
        renderHPBar(100 - player2.HP , 2);

        if(player1.HP <= 0 or player2.HP <= 0){
            if(player1.HP <= 0){
                player1.Dead();
            }
            if(player2.HP <= 0){
                player2.Dead();
            }
        }
    // PRESENT RENDERER
        SDL_RenderPresent(gRenderer);
    // MANAGE FPS
        frameTime = SDL_GetTicks() - currentFrameTime;
        if (frameTime < TARGET_FRAME_TIME) {
            SDL_Delay(TARGET_FRAME_TIME - frameTime);
        }
    }
    EndGame();
    return;
}
