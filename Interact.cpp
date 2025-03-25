#include "Interact.h"


void interactProcess(){
    if(player1.Status == MOVEMENT_ATTACK or player2.Status == MOVEMENT_ATTACK){
            checkHit();
        }
        else{
            player1.updateDirection(player2.oX,player2.oY);
            player2.updateDirection(player1.oX,player1.oY);
        }
        P1_Symbol.render(player1.oX + HeroLists[player1.heroCode].body.x,player1.oY + (HeroLists[player1.heroCode].body.y - 26), 0 , 0 ,25,26,0);
        P2_Symbol.render(player2.oX + HeroLists[player2.heroCode].body.x,player2.oY + (HeroLists[player2.heroCode].body.y - 26), 0 , 0 ,25,26,0);
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
}
void checkHit(){
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
