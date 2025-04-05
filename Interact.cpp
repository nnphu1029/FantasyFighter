#include "Interact.h"

Object P1_Symbol(0);
Object P2_Symbol(0);
SDL_Texture* P1_HpBar = NULL;
SDL_Texture* P2_HpBar = NULL;
SDL_Texture* P1_ava = NULL;
SDL_Texture* P2_ava = NULL;


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

void updateZoom(){
    SDL_Rect camera = {0,0,scrWidth , scrHeight};
    int left = min(player1.oX + (HeroData[player1.heroCode].frWidth/2) - 15,
                   player2.oX + (HeroData[player2.heroCode].frWidth/2) - 15);
    int right = max(player1.oX + (HeroData[player1.heroCode].frWidth/2) + 15,
                   player2.oX + (HeroData[player2.heroCode].frWidth/2) + 15);

    camera.w = max(right - left , 780);
    camera.x = min((right + left)/2  - camera.w/2,scrWidth - camera.w);
    camera.x = max(camera.x,0);
    camera.h = camera.w/2;
    camera.y = scrHeight - camera.h;

    SDL_RenderCopy(gRenderer,presentTexture,&camera,NULL);
    return;
}

void interactProcess(){
    P1_Symbol.render(player1.oX + (HeroData[player1.heroCode].frWidth/2) - 15,player1.oY + 50, 0 , 0 ,25,26,0);
    P2_Symbol.render(player2.oX + (HeroData[player2.heroCode].frWidth/2) - 15,player2.oY + 50, 0 , 0 ,25,26,0);
    checkHit();
    player1.updateDirection(player2.oX + (HeroData[player2.heroCode].frWidth/2) - 15 , player1.oX + (HeroData[player1.heroCode].frWidth/2) - 15);
    player2.updateDirection(player1.oX + (HeroData[player1.heroCode].frWidth/2) - 15 , player2.oX + (HeroData[player2.heroCode].frWidth/2) - 15);

    if(player1.HP <= 0 or player2.HP <= 0){
        if(player1.HP <= 0){
            player1.Dead();
            cout << "player 2 Win" << endl;
        }
        if(player2.HP <= 0){
            player2.Dead();
            cout << "player 1 Win" << endl;
        }
        CheckPause = true;
    }
    return;
}

bool checkStateAttack(int type){
    if(type == 1){
        return ((player1.Status >= MOVEMENT_ATTACK1 and player1.Status <= MOVEMENT_SPSKILL)
                or (player1.Status == MOVEMENT_AIRATTACK));
    }
    else if(type == 2){
        return ((player2.Status >= MOVEMENT_ATTACK1 and player2.Status <= MOVEMENT_SPSKILL)
                or (player2.Status == MOVEMENT_AIRATTACK));
    }
    return false;
}

void checkHit(){
    if(checkStateAttack(1) and checkStateAttack(2)){
        if(SDL_HasIntersection(&player1.hitbox,&player2.hitbox)){
            if(player1.getAttackFrame() == 4){
                player1.AirBorne();
                player2.AirBorne();
            }
            return;
        }
    }
    else{
        int dame = 0;
        if(checkStateAttack(2)){
            if(SDL_HasIntersection(&player2.hitbox,&player1.mainBody)){
                if(player1.Status == MOVEMENT_BLOCK) return;
                switch (player2.Status){
                    case MOVEMENT_ATTACK1:
                        dame = HeroData[player2.heroCode].AttackFrame1.dame*
                        (player2.getAttackFrame() + 1 == HeroData[player2.heroCode].AttackFrame1.numberFrame);
                        break;
                    case MOVEMENT_ATTACK2:
                        dame = HeroData[player2.heroCode].AttackFrame2.dame*
                        (player2.getAttackFrame() + 1 == HeroData[player2.heroCode].AttackFrame2.numberFrame);
                        break;
                    case MOVEMENT_ATTACK3:
                        dame = HeroData[player2.heroCode].AttackFrame3.dame*
                        (player2.getAttackFrame() + 1 == HeroData[player2.heroCode].AttackFrame3.numberFrame);
                        break;
                    case MOVEMENT_AIRATTACK:
                        dame = HeroData[player2.heroCode].AirAttack.dame*
                        (player2.getAttackFrame() + 1 == HeroData[player2.heroCode].AirAttack.numberFrame);
                        break;
                    case MOVEMENT_SPSKILL:
                        dame = HeroData[player2.heroCode].SpecSkill.dame*
                        (player2.getAttackFrame() + 1 == HeroData[player2.heroCode].SpecSkill.numberFrame - 2);
                        break;
                }
                if(dame != 0){
                    player1.Hurt(dame);
                }
                orderRender = 1;
            }
        }
        else{
            if(checkStateAttack(1)){
                if(SDL_HasIntersection(&player1.hitbox,&player2.mainBody)){
                    if(player2.Status == MOVEMENT_BLOCK) return;
                    switch (player1.Status){
                        case MOVEMENT_ATTACK1:
                            dame = HeroData[player1.heroCode].AttackFrame1.dame*
                            (player1.getAttackFrame() + 1 == HeroData[player1.heroCode].AttackFrame1.numberFrame);
                            break;
                        case MOVEMENT_ATTACK2:
                            dame = HeroData[player1.heroCode].AttackFrame2.dame*
                            (player1.getAttackFrame() + 1 == HeroData[player1.heroCode].AttackFrame2.numberFrame);
                            break;
                        case MOVEMENT_ATTACK3:
                            dame = HeroData[player1.heroCode].AttackFrame3.dame*
                            (player1.getAttackFrame() + 1 == HeroData[player1.heroCode].AttackFrame3.numberFrame);
                            break;
                        case MOVEMENT_AIRATTACK:
                            dame = HeroData[player1.heroCode].AirAttack.dame*
                            (player1.getAttackFrame() + 1 == HeroData[player1.heroCode].AirAttack.numberFrame);
                            break;
                        case MOVEMENT_SPSKILL:
                            dame = HeroData[player1.heroCode].SpecSkill.dame*
                            (player1.getAttackFrame() + 1 == HeroData[player1.heroCode].SpecSkill.numberFrame - 2);
                            break;
                    }
                    if(dame != 0){
                        player2.Hurt(dame);
                    }
                    orderRender = 2;
                }
            }
        }
    }
    return;
}

void renderHPBar(int hpFrame , int type) {
    SDL_Rect renderObject = { 0 , hpFrame * 100 , 500 , 100};
    if(type == 1){
        SDL_Rect renderP1= { 0 , 0 , 500 , 100};
        SDL_RenderCopy(gRenderer, P1_HpBar ,&renderObject , &renderP1);
    }
    else{
        SDL_Rect renderP2 = { 700 , 0 , 500 , 100};
        SDL_RenderCopy(gRenderer, P2_HpBar ,&renderObject , &renderP2);
    }
}

void renderAvatar(int type){
    if(type == 1){
        SDL_Rect renderP1 = {0,0,95,95};
        SDL_RenderCopy(gRenderer,P1_ava,NULL,&renderP1);
    }
    else{
        SDL_Rect renderP2 = {scrWidth - 95,0,95,95};
        SDL_RenderCopyEx(gRenderer,P2_ava,NULL,&renderP2,NULL,NULL,SDL_FLIP_HORIZONTAL);
    }
}
