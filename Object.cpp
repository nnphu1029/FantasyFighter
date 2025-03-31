#include "Object.h"

Object::Object(int type){
    heroCode = 0;
    oTexture = NULL;
    oWidth = 0 , oHeight = 0;
    frame = FRAMERESET;
    if(type != 0){
        HP = 100;
        oX = PLAYER1X * (type == 1) +  PLAYER2X * (type == 2);
        oY = 0;
        veloX = 0 , veloY = 0;
        Status = MOVEMENT_IDLE;

        maxJump = PLAYERY;
        frame = FRAMERESET;
        Direction = DIRECTION_RIGHT * (type == 1) + DIRECTION_LEFT * (type == 2);

        checkDoubleJump = false;
        checkHurt = false;
        checkAttack = false;

        beginCastTime = SDL_GetTicks();
        startCooldown = SDL_GetTicks();
    }
}


int Object::getWidth(){ return oWidth;}

int Object::getHeight(){ return oHeight;}

SDL_Texture* Object::getTexture(){ return oTexture;}

int Object::getAttackFrame(){ return frame;}

void Object::Jump(){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT or checkAttack == true) return;
    if(oY > PLAYERY)  oY = PLAYERY;
    if(oY < PLAYERY){
        if(checkDoubleJump == true) return;
        checkDoubleJump = true;
        maxJump = max(oY - 125,0);
    }
    else maxJump = max(oY - 225,0);
    frame = FRAMERESET;
    veloY = -2.00;
}

void Object::Dash(){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT or checkAttack == true or Status == MOVEMENT_DASH){
        return;
    }
    veloX =  30 * Direction;
    Status = MOVEMENT_DASH;
    xUpdate();
    frame = FRAMERESET;
}

void Object::Attack(){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT or checkHurt == true) return;
    if(checkAttack == true){
        if(Status == MOVEMENT_ATTACK1){
            oX +=  2*Direction;
            Status = MOVEMENT_ATTACK2;
        }
        else if(Status == MOVEMENT_ATTACK2){
            oX +=  2*Direction;
            Status = MOVEMENT_ATTACK3;
        }
        return;
    }
    else{
        beginCastTime = SDL_GetTicks();
        checkAttack = true;
        veloX = 0;
        frame = FRAMERESET;
        if(Status != MOVEMENT_SPSKILL){
            if(oY < PLAYERY){
                Status = MOVEMENT_AIRATTACK;
            }
            else{
                Status = MOVEMENT_ATTACK1;
            }
        }
    }
    return;
}

void Object::SpecAttack(){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT or checkAttack == true) return;
    if(Status == MOVEMENT_SPSKILL) return;
    checkCooldown = SDL_GetTicks();
    if(checkCooldown - startCooldown >= SPECCOOLDOWN){
        Status = MOVEMENT_SPSKILL;
        Attack();
    }
    return;
}

void Object::castAttack(){
    frame = frame + 1;
    if(Status == MOVEMENT_ATTACK1 and (frame == HeroData[heroCode].AttackFrame1.numberFrame)){
        endCastTime = SDL_GetTicks();
        if(endCastTime - beginCastTime < ATTACKTIME){
            frame = frame - 1;
        }
        else{
            checkAttack = false;
            return;
        }
    }
    else if(Status == MOVEMENT_ATTACK2 and (frame == HeroData[heroCode].AttackFrame2.numberFrame)){
        endCastTime = SDL_GetTicks();
        if(endCastTime - beginCastTime < 2*ATTACKTIME - 50){
            frame = frame - 1;
        }
        else{
            checkAttack = false;
            return;
        }
    }
    else if(Status == MOVEMENT_ATTACK3 and (frame == HeroData[heroCode].AttackFrame3.numberFrame)){
        endCastTime = SDL_GetTicks();
        if(endCastTime - beginCastTime < 3*ATTACKTIME - 100){
            frame = frame - 1;
        }
        else{
            checkAttack = false;
            return;
        }
    }
    else if(Status == MOVEMENT_AIRATTACK and (frame == HeroData[heroCode].AirAttack.numberFrame)){
        endCastTime = SDL_GetTicks();
        if(endCastTime - beginCastTime < ATTACKTIME + 20){
            frame = frame - 1;
        }
        else{
            checkAttack = false;
            return;
        }
    }
    else if(Status == MOVEMENT_SPSKILL and (frame == HeroData[heroCode].SpecSkill.numberFrame)){
        endCastTime = SDL_GetTicks();
        if(endCastTime - beginCastTime < 3*ATTACKTIME - 500){
            frame = frame - 2;
        }
        else{
            startCooldown = SDL_GetTicks();
            checkAttack = false;
            return;
        }
    }
}

void Object::Block(){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT or checkAttack == true) return;
    if(Status == MOVEMENT_BLOCK){
        return;
    }
    veloX = 0;
    frame = FRAMERESET;
    Status = MOVEMENT_BLOCK;
    return;
}

void Object::Hurt(int dame){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT) return;
    Status = MOVEMENT_HURT;
    veloX = 0;
    veloY = 0;
    if(checkHurt != true){
        HP = max(0,HP - dame);
    }
    checkHurt = true;
    frame = FRAMERESET;
}

void Object::Dead(){
    if(Status == MOVEMENT_DEATH) return;
    Status = MOVEMENT_DEATH;
    frame = FRAMERESET;
}

void Object::Gravity(){
    if(Status == MOVEMENT_DEATH) return;
    if(checkAttack == true) return;
    if(oY > PLAYERY) oY = PLAYERY;
    if(oY == PLAYERY){
        if(veloY < 0) veloY = veloY - gravityAccel;
        else{
            veloY = 0;
            checkDoubleJump = false;

        }
    }
    else if(oY < PLAYERY){
        if(oY > maxJump){
            if(veloY < 0){
                veloY = veloY - gravityAccel;
                veloY = max(veloY,(float)-30.0);
            }
            else{
                veloY = veloY + gravityAccel;
                veloY = min(veloY,(float)30.0);
            }
        }
        else if(oY <= maxJump){
            if(veloY < 0) veloY = 0.00;
            else{
                veloY = veloY + gravityAccel;
                veloY = min(veloY,(float)30.0);
            }
        }
    }
}

void Object::castMoving(int type){
    if ((objectFlag[SDL_SCANCODE_A] and type == 1) or (objectFlag[SDL_SCANCODE_LEFT] and type == 2)) {
        if(Direction != DIRECTION_LEFT){
            frame = FRAMERESET;
            Direction = DIRECTION_LEFT;
            veloX = 0;
        }
        if(Status != MOVEMENT_MOVE){
            Status = MOVEMENT_MOVE;
        }
        veloX = max(veloX - gravityAccel, (float)-20);
    }
    else if((objectFlag[SDL_SCANCODE_D] and type == 1) or (objectFlag[SDL_SCANCODE_RIGHT] and type == 2)) {
        if(Direction != DIRECTION_RIGHT){
            frame = FRAMERESET;
            Direction = DIRECTION_RIGHT;
            veloX = 0;
        }
        if(Status != MOVEMENT_MOVE){
            Status = MOVEMENT_MOVE;
        }
        veloX = min(veloX + gravityAccel, (float)20);
    }
    else{
        Status = MOVEMENT_IDLE;
        veloX = 0;
    }
    return;
}

void Object::movementUpdate(int frameWidth , int frameHeight, int type){
    if(Status != MOVEMENT_DEATH){
        if(checkAttack == true){
            castAttack();
            updateHitBox(frameWidth,frameHeight);
            if(checkAttack == false){
                frame = FRAMERESET;
                Status = MOVEMENT_IDLE;
            }
            else{
                veloX = 0;
                veloY = 0;
            }
        }
        else if(checkHurt == true){
            Status = MOVEMENT_HURT;
            frame = (frame + 1);
            if(frame >= HeroData[heroCode].HurtFrame){
                checkHurt = false;
                Status = MOVEMENT_IDLE;
                frame = FRAMERESET;
                return;
            }
        }
        else{
            if(Status == MOVEMENT_DASH){
                frame = (frame + 1);
                if(frame == HeroData[heroCode].DashFrame){
                    Status = MOVEMENT_IDLE;
                }
            }
            else if(Status == MOVEMENT_BLOCK){
                if((objectFlag[SDL_SCANCODE_S] and type == 1) or (objectFlag[SDL_SCANCODE_DOWN] and type == 2)){
                   veloX = 0;
                    frame = frame + 1;
                    if(frame == HeroData[heroCode].BlockFrame){
                        frame = frame - 1;
                    }
                }
                else{
                    Status = MOVEMENT_IDLE;
                    frame = FRAMERESET;
                }
            }
            else{
                castMoving(type);
                frame = (frame + 1)%HeroData[heroCode].MovingFrame;
            }
        }
        Gravity();
        xUpdate();
        yUpdate();
        updateMainBody(frameWidth,frameWidth);
    }
    else{
        Status = MOVEMENT_DEATH;
        frame = frame + 1;
        if(frame == HeroData[heroCode].DeadFrame){
            frame -= 1;
        }
    }
    render(oX , oY  , frame * HeroData[heroCode].frWidth ,  Status * HeroData[heroCode].frHeight ,
           HeroData[heroCode].frWidth , HeroData[heroCode].frHeight, 1 * (Direction == DIRECTION_LEFT));
}

void Object::render( int a, int b, int x, int y, int iWidth, int iHeight, int checkFlip) {
    SDL_Rect renderObject = { x, y, iWidth , iHeight };
    if(checkFlip == 3){
        SDL_Rect renderTexture = { a, b, scrWidth, scrHeight };
        SDL_RenderCopy(gRenderer, oTexture,&renderObject , &renderTexture);
    }
    else{
        SDL_Rect renderTexture = { a, b, iWidth, iHeight };
        if(checkFlip == 0){
            SDL_RenderCopy(gRenderer, oTexture,&renderObject , &renderTexture);
        }
        else{
            SDL_RenderCopyEx(gRenderer, oTexture,&renderObject , &renderTexture,0,NULL,SDL_FLIP_HORIZONTAL);
        }
    }
}

void Object::ZA_WARUDO(){
    render(oX , oY  , frame * HeroData[heroCode].frWidth ,  Status * HeroData[heroCode].frHeight ,
           HeroData[heroCode].frWidth , HeroData[heroCode].frHeight, 1 * (Direction == DIRECTION_LEFT));
}

void Object::updateDirection(int a , int b){
    if(Status != MOVEMENT_IDLE) return;
    if(Direction == DIRECTION_LEFT){
        if(b < a){
            Direction = DIRECTION_RIGHT;
        }
    }
    if(Direction == DIRECTION_RIGHT){
        if(a < b){
            Direction = DIRECTION_LEFT;
        }
    }
}

bool Object::loadFromFile(string path){
    deleteObject(0);
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = NULL;

    loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        cout << "Loaded image failed: " << path << endl;
    }
    else{
        SDL_SetColorKey(loadedSurface , SDL_TRUE , SDL_MapRGB(loadedSurface->format, 85, 89, 91 ));
        //85, 89, 91
        //55595B
        newTexture = SDL_CreateTextureFromSurface(gRenderer , loadedSurface);
        if(newTexture == NULL){
            cout << "Creating newTexture failed" << endl;
        }
        else{
            oHeight = loadedSurface->h;
            oWidth = loadedSurface->w;
        }
        SDL_FreeSurface(loadedSurface);
    }
    oTexture = newTexture;
    return(oTexture != NULL);
}

void Object::deleteObject(int type){
    SDL_DestroyTexture(oTexture);
    oTexture = NULL;
    oWidth = 0 , oHeight = 0;
    frame = FRAMERESET;
    if(type != 0){
        HP = 100;
        oX = PLAYER1X * (type == 1) +  PLAYER2X * (type == 2);
        oY = 0;
        veloX = 0 , veloY = 0;
        Status = MOVEMENT_IDLE;
        maxJump = PLAYERY;
        checkDoubleJump = false;
        checkHurt = false;
        checkAttack = false;
        frame = FRAMERESET;
        Direction = DIRECTION_RIGHT * (type == 1) + DIRECTION_LEFT * (type == 2);
    }
}

void Object::xUpdate(){
    oX = oX + (int)veloX;
    oX = max(oX , limitP1);
    oX = min(oX , limitP2);
}

void Object::yUpdate(){
    oY = oY + (int)veloY;
    oY = min(oY , PLAYERY);
    oY = max(oY , 0);
    if(checkAttack != true){
        if(veloY < 0){
            Status = MOVEMENT_JUMP;
            frame = (frame + 1)%HeroData[heroCode].JumpFallFrame;
        }
        else if(veloY > 0){
            Status = MOVEMENT_FALL;
            frame = (frame + 1)%HeroData[heroCode].JumpFallFrame;
        }
    }
}

void Object::updateHitBox(int frameWidth, int frameHeight){
    switch (Status){
        case MOVEMENT_ATTACK1:
            if(Direction == DIRECTION_RIGHT){
                hitbox = {oX + HeroData[heroCode].AttackFrame1.hitAOE.x , oY , HeroData[heroCode].AttackFrame1.hitAOE.w , HeroData[heroCode].AttackFrame1.hitAOE.h};
            }
            else{
                hitbox = {oX + frameWidth - HeroData[heroCode].AttackFrame1.hitAOE.x - HeroData[heroCode].AttackFrame1.hitAOE.w, oY , HeroData[heroCode].AttackFrame1.hitAOE.w , HeroData[heroCode].AttackFrame1.hitAOE.h};
            }
            break;
        case MOVEMENT_ATTACK2:
            if(Direction == DIRECTION_RIGHT){
                hitbox = {oX + HeroData[heroCode].AttackFrame2.hitAOE.x , oY , HeroData[heroCode].AttackFrame2.hitAOE.w , HeroData[heroCode].AttackFrame2.hitAOE.h};
            }
            else{
                hitbox = {oX + frameWidth - HeroData[heroCode].AttackFrame2.hitAOE.x - HeroData[heroCode].AttackFrame2.hitAOE.w, oY , HeroData[heroCode].AttackFrame2.hitAOE.w , HeroData[heroCode].AttackFrame2.hitAOE.h};
            }
            break;
        case MOVEMENT_ATTACK3:
            if(Direction == DIRECTION_RIGHT){
                hitbox = {oX + HeroData[heroCode].AttackFrame3.hitAOE.x , oY , HeroData[heroCode].AttackFrame3.hitAOE.w , HeroData[heroCode].AttackFrame3.hitAOE.h};
            }
            else{
                hitbox = {oX + frameWidth - HeroData[heroCode].AttackFrame3.hitAOE.x - HeroData[heroCode].AttackFrame3.hitAOE.w, oY , HeroData[heroCode].AttackFrame3.hitAOE.w , HeroData[heroCode].AttackFrame3.hitAOE.h};
            }
            break;
        case MOVEMENT_AIRATTACK:
            if(Direction == DIRECTION_RIGHT){
                hitbox = {oX + HeroData[heroCode].AirAttack.hitAOE.x , oY , HeroData[heroCode].AirAttack.hitAOE.w , HeroData[heroCode].AirAttack.hitAOE.h};
            }
            else{
                hitbox = {oX + frameWidth - HeroData[heroCode].AirAttack.hitAOE.x - HeroData[heroCode].AirAttack.hitAOE.w, oY , HeroData[heroCode].AirAttack.hitAOE.w , HeroData[heroCode].AirAttack.hitAOE.h};
            }
            break;
        case MOVEMENT_SPSKILL:
            if(Direction == DIRECTION_RIGHT){
                hitbox = {oX + HeroData[heroCode].SpecSkill.hitAOE.x , oY , HeroData[heroCode].SpecSkill.hitAOE.w , HeroData[heroCode].SpecSkill.hitAOE.h};
            }
            else{
                hitbox = {oX + frameWidth - HeroData[heroCode].SpecSkill.hitAOE.x - HeroData[heroCode].SpecSkill.hitAOE.w, oY , HeroData[heroCode].SpecSkill.hitAOE.w , HeroData[heroCode].SpecSkill.hitAOE.h};
            }
            break;
        default:
            break;
    }
}

void Object::updateMainBody(int frameWidth, int frameHeight){
    if(Direction == DIRECTION_RIGHT){
        mainBody = {oX + HeroData[heroCode].body.x,oY,HeroData[heroCode].body.w,HeroData[heroCode].body.h};
    }
    else{
        mainBody = {oX + frameWidth - HeroData[heroCode].body.x - HeroData[heroCode].body.w, oY , HeroData[heroCode].body.w,HeroData[heroCode].body.h};
    }
}



