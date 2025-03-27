#include "Interact.h"

bool MouseClick(SDL_Rect mouseZone){
    int x, y;
    SDL_GetMouseState(&x , &y);
    if((x >= mouseZone.x and x <= (mouseZone.x + mouseZone.w)) and
       (y >= mouseZone.y and y <= (mouseZone.y + mouseZone.h))){
        Uint32 checkClick = SDL_GetMouseState(NULL,NULL);
        return (checkClick & SDL_BUTTON(SDL_BUTTON_LEFT));
    }
    return false;
}

bool mouseInButton(SDL_Rect mouseZone){
    int x, y;
    SDL_GetMouseState(&x , &y);
    return((x >= mouseZone.x and x <= (mouseZone.x + mouseZone.w)) and (y >= mouseZone.y and y <= (mouseZone.y + mouseZone.h)));
}

void interactProcess(){
    if(player1.Status == MOVEMENT_ATTACK or player2.Status == MOVEMENT_ATTACK){
            checkHit();
        }
        else{
            player1.updateDirection(player2.oX);
            player2.updateDirection(player1.oX);
        }
        P1_Symbol.render(player1.oX + HeroData[player1.heroCode].body.x,player1.oY + (HeroData[player1.heroCode].body.y - 26), 0 , 0 ,25,26,0);
        P2_Symbol.render(player2.oX + HeroData[player2.heroCode].body.x,player2.oY + (HeroData[player2.heroCode].body.y - 26), 0 , 0 ,25,26,0);

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
        int dame;
        if(player1.Status == MOVEMENT_ATTACK){
            if(SDL_HasIntersection(&player1.hitbox,&player2.mainBody)){
                switch (player1.getMultiAttack()){
                    case 1:
                        dame = HeroData[player1.heroCode].AttackFrame1.dame;
                        break;
                    case 2:
                        dame = HeroData[player1.heroCode].AttackFrame2.dame;
                        break;
                    case 3:
                        dame = HeroData[player1.heroCode].AttackFrame3.dame;
                        break;
                    default:
                        break;
                }
                player2.Hurt(dame);
                orderRender = 2;
            }
        }
        else if(player2.Status == MOVEMENT_ATTACK){
            if(SDL_HasIntersection(&player2.hitbox,&player1.mainBody)){

                switch (player2.getMultiAttack()){
                    case 1:
                        dame = HeroData[player2.heroCode].AttackFrame1.dame;
                        break;
                    case 2:
                        dame = HeroData[player2.heroCode].AttackFrame2.dame;
                        break;
                    case 3:
                        dame = HeroData[player2.heroCode].AttackFrame3.dame;
                        break;
                    default:
                        break;
                }
                player1.Hurt(dame);
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
