#include<SDL.h>
#include<SDL_image.h>
#include "Interact.h"
#include "const.h"
#include "Object.h"

extern Object player1;
extern Object player2;
extern int orderRender;

void interactProcess(){
    if(player1.Status == player2.Status){
        if(player1.Status == MOVEMENT_ATTACK){
            if(SDL_HasIntersection(&player1.hitbox,&player2.hitbox)){
                player2.Stun();
                player1.Stun();
            }
        }
    }
    else{
        if(player1.Status == MOVEMENT_ATTACK){
            if(SDL_HasIntersection(&player1.hitbox,&player2.mainBody)){
                player2.Hurt();
                orderRender = 2;
            }
        }
        else if(player2.Status == MOVEMENT_ATTACK){
            if(SDL_HasIntersection(&player2.hitbox,&player1.mainBody)){
                player1.Hurt();
                orderRender = 1;
            }
        }
    }
}

void renderHPBar(int hpFrame , int type) {
    SDL_Rect renderObject = { 0 , hpFrame * 100 , 500 , 100};
    if(type == 1){
        SDL_Rect renderTexture = { 0 , 0 , 500 , 100};
        SDL_RenderCopy(gRenderer, P1_HpBar ,&renderObject , &renderTexture);
    }
    else{
        SDL_Rect renderTexture = { 700 , 0 , 500 , 100};
        SDL_RenderCopy(gRenderer, P2_HpBar ,&renderObject , &renderTexture);
    }
}
