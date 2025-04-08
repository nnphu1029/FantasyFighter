#include "Interact.h"

Object P1_Symbol(0);
Object P2_Symbol(0);
SDL_Texture* P1_HpBar = NULL;
SDL_Texture* P2_HpBar = NULL;
SDL_Texture* P1_ava = NULL;
SDL_Texture* P2_ava = NULL;
SDL_Rect WinnerCamera = {0,350,500,250};

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
    if(Winner != -1){
        SDL_RenderCopy(gRenderer,presentTexture,&WinnerCamera,NULL);
        return;
    }
    SDL_Rect camera = {0,0,scrWidth , scrHeight};
    int left = min(player1.oX + (HeroData[player1.heroCode].frWidth/2) - 15,
                   player2.oX + (HeroData[player2.heroCode].frWidth/2) - 15);
    int right = max(player1.oX + (HeroData[player1.heroCode].frWidth/2) + 15,
                   player2.oX + (HeroData[player2.heroCode].frWidth/2) + 15);

    camera.w = max(right - left , 790);
    camera.x = min((right + left)/2  - camera.w/2,scrWidth - camera.w);
    camera.x = max(camera.x,0);
    camera.h = camera.w/2;
    camera.y = scrHeight - camera.h;

    SDL_RenderCopy(gRenderer,presentTexture,&camera,NULL);

    return;
}

void interactProcess(){
    if(Winner == -1){
        P1_Symbol.render(player1.oX + (HeroData[player1.heroCode].frWidth/2) - 15,player1.oY + 50, 0 , 0 ,25,26,0);
        P2_Symbol.render(player2.oX + (HeroData[player2.heroCode].frWidth/2) - 15,player2.oY + 50, 0 , 0 ,25,26,0);
    }
    checkHit();
    player1.updateDirection(player2.oX + (HeroData[player2.heroCode].frWidth/2) - 15 , player1.oX + (HeroData[player1.heroCode].frWidth/2) - 15);
    player2.updateDirection(player1.oX + (HeroData[player1.heroCode].frWidth/2) - 15 , player2.oX + (HeroData[player2.heroCode].frWidth/2) - 15);

    if(player1.HP <= 0 or player2.HP <= 0){
        if(player1.HP <= 0){
            player1.Dead();
            Winner = 2;
            WinnerCamera.x = max(min(player2.oX + HeroData[player2.heroCode].frWidth/2 - 250,700),0);
            player2.checkIf_I_Win = true;
        }
        if(player2.HP <= 0){
            player2.Dead();
            Winner = 1;
            WinnerCamera.x = max(min(player1.oX + HeroData[player1.heroCode].frWidth/2 - 250,700),0);
            player1.checkIf_I_Win = true;
        }
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
            if((player2.getAttackFrame() >= HeroData[player1.heroCode].SpecSkill.TakeHitframe)
                or (player2.getAttackFrame() >= HeroData[player1.heroCode].AirAttack.TakeHitframe)
                or (player2.getAttackFrame() >= HeroData[player1.heroCode].AttackFrame1.TakeHitframe)
                or (player2.getAttackFrame() >= HeroData[player1.heroCode].AttackFrame2.TakeHitframe)
                or (player2.getAttackFrame() >= HeroData[player1.heroCode].AttackFrame3.TakeHitframe)){
                player1.AirBorne(5);
                player2.AirBorne(5);
            }
            return;
        }
    }
    else{
        int dame = 0;
        int Status = 0;
        if(checkStateAttack(2)){
            if(SDL_HasIntersection(&player2.hitbox,&player1.mainBody)){
                switch (player2.Status){
                    case MOVEMENT_SPSKILL:
                        dame = HeroData[player2.heroCode].SpecSkill.dame*
                        (player2.getAttackFrame() == HeroData[player2.heroCode].SpecSkill.TakeHitframe);
                        Status = HeroData[player2.heroCode].SpecSkill.effect*
                        (player2.getAttackFrame() >= HeroData[player2.heroCode].SpecSkill.TakeHitframe);
                        break;
                    case MOVEMENT_AIRATTACK:
                        dame = HeroData[player2.heroCode].AirAttack.dame*
                        (player2.getAttackFrame() == HeroData[player2.heroCode].AirAttack.TakeHitframe);
                        Status = HeroData[player2.heroCode].AirAttack.effect*
                        (player2.getAttackFrame() >= HeroData[player2.heroCode].AirAttack.TakeHitframe);
                        break;
                    default:
                        switch (player2.Status){
                            case MOVEMENT_ATTACK1:
                                dame = HeroData[player2.heroCode].AttackFrame1.dame * (player2.getAttackFrame() == HeroData[player2.heroCode].AttackFrame1.TakeHitframe);
                                Status = HeroData[player2.heroCode].AttackFrame1.effect*
                                (player2.getAttackFrame() >= HeroData[player2.heroCode].AttackFrame1.TakeHitframe);
                                break;
                            case MOVEMENT_ATTACK2:
                                dame = HeroData[player2.heroCode].AttackFrame1.dame * (player2.getAttackFrame() == HeroData[player2.heroCode].AttackFrame1.TakeHitframe);
                                dame = HeroData[player2.heroCode].AttackFrame2.dame * (player2.getAttackFrame() == HeroData[player2.heroCode].AttackFrame2.TakeHitframe);
                                Status = HeroData[player2.heroCode].AttackFrame2.effect*
                                (player2.getAttackFrame() >= HeroData[player2.heroCode].AttackFrame2.TakeHitframe);
                                break;
                            case MOVEMENT_ATTACK3:
                                dame = HeroData[player2.heroCode].AttackFrame1.dame * (player2.getAttackFrame() == HeroData[player2.heroCode].AttackFrame1.TakeHitframe);
                                dame = HeroData[player2.heroCode].AttackFrame2.dame * (player2.getAttackFrame() == HeroData[player2.heroCode].AttackFrame2.TakeHitframe);
                                dame = HeroData[player2.heroCode].AttackFrame3.dame * (player2.getAttackFrame() == HeroData[player2.heroCode].AttackFrame3.TakeHitframe);
                                Status = HeroData[player2.heroCode].AttackFrame3.effect*
                                (player2.getAttackFrame() >= HeroData[player2.heroCode].AttackFrame3.TakeHitframe);
                                break;
                        }
                        break;
                }
                if(player1.Status == MOVEMENT_BLOCK and Status != SHIELD_BREAK){
                    dame = dame/2;
                }
                switch (Status){
                    case AIRBORNE:
                        if(player1.Status != MOVEMENT_BLOCK){
                            player1.AirBorne(dame);
                        }
                        else{
                            if(dame != 0){
                                player1.Hurt(dame);
                            }
                        }
                        break;
                    case HARASS:
                        dame = HeroData[player2.heroCode].SpecSkill.dame;
                        if(player1.Status == MOVEMENT_BLOCK){
                            dame = dame/2;
                        }
                        player1.Hurt(dame);
                        break;
                    case HP_STEAL:
                        if(dame != 0){
                            if(player1.Status != MOVEMENT_BLOCK){
                                player1.Hurt(dame);
                            }
                            else player1.HP = max(player1.HP - dame,0);
                            player2.HP = min(player2.HP + (dame/2),100);
                        }

                        break;
                    case SHIELD_BREAK:
                        if(player1.Status == MOVEMENT_BLOCK){
                            player1.ShieldBreak(dame);
                        }
                        else player1.Hurt(dame);
                        break;
                    case NONE:
                        if(dame != 0){
                            player1.Hurt(dame);
                        }
                        break;
                    default:
                        player1.Hurt(dame);
                        break;
                }
                orderRender = 1;
            }
        }
        else{
            if(checkStateAttack(1)){
                if(SDL_HasIntersection(&player1.hitbox,&player2.mainBody)){
                    switch (player1.Status){
                        case MOVEMENT_SPSKILL:
                            dame = HeroData[player1.heroCode].SpecSkill.dame*
                            (player1.getAttackFrame() == HeroData[player1.heroCode].SpecSkill.TakeHitframe);
                            Status = HeroData[player1.heroCode].SpecSkill.effect*
                            (player1.getAttackFrame() >= HeroData[player1.heroCode].SpecSkill.TakeHitframe);
                            break;
                        case MOVEMENT_AIRATTACK:
                            dame = HeroData[player1.heroCode].AirAttack.dame*
                            (player1.getAttackFrame() == HeroData[player1.heroCode].AirAttack.TakeHitframe);
                            Status = HeroData[player1.heroCode].AirAttack.effect*
                            (player1.getAttackFrame() >= HeroData[player1.heroCode].AirAttack.TakeHitframe);
                            break;
                        default:
                            switch (player1.Status){
                                case MOVEMENT_ATTACK1:
                                    dame = HeroData[player1.heroCode].AttackFrame1.dame * (player1.getAttackFrame() == HeroData[player1.heroCode].AttackFrame1.TakeHitframe);
                                    Status = HeroData[player1.heroCode].AttackFrame1.effect*
                                    (player1.getAttackFrame() >= HeroData[player1.heroCode].AttackFrame1.TakeHitframe);
                                    break;
                                case MOVEMENT_ATTACK2:
                                    dame = HeroData[player1.heroCode].AttackFrame1.dame * (player1.getAttackFrame() == HeroData[player1.heroCode].AttackFrame1.TakeHitframe);
                                    dame = HeroData[player1.heroCode].AttackFrame2.dame * (player1.getAttackFrame() == HeroData[player1.heroCode].AttackFrame2.TakeHitframe);
                                    Status = HeroData[player1.heroCode].AttackFrame2.effect*
                                    (player1.getAttackFrame() >= HeroData[player1.heroCode].AttackFrame2.TakeHitframe);
                                    break;
                                case MOVEMENT_ATTACK3:
                                    dame = HeroData[player1.heroCode].AttackFrame1.dame * (player1.getAttackFrame() == HeroData[player1.heroCode].AttackFrame1.TakeHitframe);
                                    dame = HeroData[player1.heroCode].AttackFrame2.dame * (player1.getAttackFrame() == HeroData[player1.heroCode].AttackFrame2.TakeHitframe);
                                    dame = HeroData[player1.heroCode].AttackFrame3.dame * (player1.getAttackFrame() == HeroData[player1.heroCode].AttackFrame3.TakeHitframe);
                                    Status = HeroData[player1.heroCode].AttackFrame3.effect*
                                    (player1.getAttackFrame() >= HeroData[player1.heroCode].AttackFrame3.TakeHitframe);
                                    break;
                            }
                            break;
                    }
                    if(player2.Status == MOVEMENT_BLOCK and Status != SHIELD_BREAK){
                        dame = dame/2;
                    }
                    switch (Status){
                        case AIRBORNE:
                            if(player2.Status != MOVEMENT_BLOCK){
                                player2.AirBorne(dame);
                            }
                            else{
                                if(dame!= 0){
                                    player2.Hurt(dame);
                                }
                            }
                            break;
                        case HARASS:
                            dame = HeroData[player1.heroCode].SpecSkill.dame;
                            if(player2.Status == MOVEMENT_BLOCK){
                                dame = dame/2;
                            }
                            player2.Hurt(dame);
                            break;
                        case HP_STEAL:
                            if(dame != 0){
                                if(player2.Status != MOVEMENT_BLOCK){
                                    player2.Hurt(dame);
                                }
                                else player2.HP = max(player2.HP - dame,0);
                                player1.HP = min(player1.HP + (dame/2),100);
                            }
                            break;
                        case SHIELD_BREAK:
                            if(player2.Status == MOVEMENT_BLOCK){
                                player2.ShieldBreak(dame);
                            }
                            else player2.Hurt(dame);
                            break;
                        case NONE:
                            if(dame != 0){
                                player2.Hurt(dame);
                            }
                            break;
                        default:
                            player2.Hurt(dame);
                            break;
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
