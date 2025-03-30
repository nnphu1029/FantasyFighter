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
        P1_Symbol.render(player1.oX + (HeroData[player1.heroCode].frWidth/2) - 12,player1.oY + 50, 0 , 0 ,25,26,0);
        P2_Symbol.render(player2.oX + (HeroData[player2.heroCode].frWidth/2) - 12,player2.oY + 50, 0 , 0 ,25,26,0);
        checkHit();
        player1.updateDirection(player2.oX + (HeroData[player2.heroCode].frWidth/2) - 12 , player1.oX + (HeroData[player1.heroCode].frWidth/2) - 12);
        player2.updateDirection(player1.oX + (HeroData[player1.heroCode].frWidth/2) - 12 , player2.oX + (HeroData[player2.heroCode].frWidth/2) - 12);
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
bool checkStateAttack(int type){
    if(type == 1){
        return ((player1.Status >= MOVEMENT_ATTACK1 and player1.Status <= MOVEMENT_SPSKILL)
                or (player1.Status == MOVEMENT_AIRATTACK));
    }
    else if(type == 2){
        return ((player2.Status >= MOVEMENT_ATTACK1 and player2.Status <= MOVEMENT_SPSKILL)
                or (player2.Status == MOVEMENT_AIRATTACK));
    }
}
void checkHit(){
    if(checkStateAttack(1) and checkStateAttack(2)){
        if(SDL_HasIntersection(&player1.hitbox,&player2.hitbox)){
                player1.veloX -= 60 * player1.Direction;
                player2.veloX -= 60 * player2.Direction;
                player1.veloY -= 20;
                player2.veloY -= 20;
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
                    orderRender = 1;
                }
//                cout << 2 << " " << dame << endl;
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
                        orderRender = 2;
                    }
//                    cout << 1 << " " << dame << endl;
                }
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
