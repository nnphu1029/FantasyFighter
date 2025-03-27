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
        checkDoubleJump = false;
        multiAttack = 0;
        checkHurt = false;
        frame = FRAMERESET;
        Direction = DIRECTION_RIGHT * (type == 1) + DIRECTION_LEFT * (type == 2);
    }
}


int Object::getWidth(){ return oWidth;}

int Object::getHeight(){ return oHeight;}
int Object::getMultiAttack(){ return multiAttack;}

SDL_Texture* Object::getTexture(){ return oTexture;}


void Object::Dash(){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT) return;
    if(Direction == DIRECTION_LEFT){
        veloX = -100;
    }
    else{
        veloX = 100;
    }
    Status = MOVEMENT_JUMP;
    xUpdate();
    frame = FRAMERESET;
}


void Object::Jump(){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT) return;
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

void Object::Attack(){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT) return;
    if(Status == MOVEMENT_ATTACK){
        if(multiAttack == 1 and HeroData[heroCode].AttackFrame2.numberFrame == 0) return;
        if(multiAttack == 2 and HeroData[heroCode].AttackFrame3.numberFrame == 0) return;
        multiAttack = min(multiAttack + 1,3);
        return;
    }
    else{
        beginCastTime = SDL_GetTicks();
        multiAttack = 1;

    }
    Status = MOVEMENT_ATTACK;
    frame = FRAMERESET;
}

void Object::Hurt(int dame){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT or checkHurt == true) return;
    veloX = 0;
    veloY = 0;
    checkHurt = true;
    HP = max(0,HP - dame);
    Status = MOVEMENT_HURT;
    frame = FRAMERESET;
}

void Object::Stun(){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT) return;
    if(frame%6 == 4 and Status == MOVEMENT_ATTACK){
        Status = MOVEMENT_HURT;
        frame = FRAMERESET;
        veloX = Direction * -50;
        xUpdate();
    }
}



void Object::Dead(){
    if(Status == MOVEMENT_DEATH) return;
    Status = MOVEMENT_DEATH;
    frame = FRAMERESET;
}

void Object::Gravity(){
    if(Status == MOVEMENT_DEATH) return;
    if(oY > PLAYERY) oY = PLAYERY;
    if(oY == PLAYERY){
        if(veloY < 0) veloY = veloY - gravityAccel;
        else{
            veloY = 0;
            maxJump = PLAYERY;
            checkDoubleJump = false;
        }
    }
    else if(oY < PLAYERY){
        if(Status == MOVEMENT_ATTACK){
            maxJump = max(oY - 75,0);
        }
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

void Object::xUpdate(){
    oX = oX + (int)veloX;
    oX = max(oX , -100);
    oX = min(oX , 1050);
}

void Object::yUpdate(){
    oY = oY + (int)veloY;
    oY = min(oY , PLAYERY);
    oY = max(oY , 0);
}

void Object::updateHitBox(int frameWidth, int frameHeight){
    switch (multiAttack){
        case 1:
            if(Direction == DIRECTION_RIGHT){
                hitbox = {oX + HeroData[heroCode].AttackFrame1.hitAOE.x , oY , HeroData[heroCode].AttackFrame1.hitAOE.w , HeroData[heroCode].AttackFrame1.hitAOE.h};
            }
            else{
                hitbox = {oX + frameWidth - HeroData[heroCode].AttackFrame1.hitAOE.x - HeroData[heroCode].AttackFrame1.hitAOE.w, oY , HeroData[heroCode].AttackFrame1.hitAOE.w , HeroData[heroCode].AttackFrame1.hitAOE.h};
            }
            break;
        case 2:
            if(Direction == DIRECTION_RIGHT){
                hitbox = {oX + HeroData[heroCode].AttackFrame2.hitAOE.x , oY , HeroData[heroCode].AttackFrame2.hitAOE.w , HeroData[heroCode].AttackFrame2.hitAOE.h};
            }
            else{
                hitbox = {oX + frameWidth - HeroData[heroCode].AttackFrame2.hitAOE.x - HeroData[heroCode].AttackFrame2.hitAOE.w, oY , HeroData[heroCode].AttackFrame2.hitAOE.w , HeroData[heroCode].AttackFrame2.hitAOE.h};
            }
            break;
        case 3:
            if(Direction == DIRECTION_RIGHT){
                hitbox = {oX + HeroData[heroCode].AttackFrame3.hitAOE.x , oY , HeroData[heroCode].AttackFrame3.hitAOE.w , HeroData[heroCode].AttackFrame3.hitAOE.h};
            }
            else{
                hitbox = {oX + frameWidth - HeroData[heroCode].AttackFrame3.hitAOE.x - HeroData[heroCode].AttackFrame3.hitAOE.w, oY , HeroData[heroCode].AttackFrame3.hitAOE.w , HeroData[heroCode].AttackFrame3.hitAOE.h};
            }
            break;
        default:
            break;
    }
}

void Object::movementUpdate(int frameWidth , int frameHeight, int type){
    int currentStatus = MOVEMENT_IDLE;
    if(Status != MOVEMENT_DEATH){
        if(Status == MOVEMENT_ATTACK){
            frame = frame + 1;
            if(multiAttack == 1 and (frame == HeroData[heroCode].AttackFrame1.numberFrame)){
                endCastTime = SDL_GetTicks();
                if(endCastTime - beginCastTime < ATTACKTIME){
                    frame -= 1;
                }
                else{
                    Status = MOVEMENT_IDLE;
                    multiAttack = 0;
                    frame = FRAMERESET;
                    return;
                }
            }

            if(multiAttack == 2 and (frame == HeroData[heroCode].AttackFrame1.numberFrame +
                                              HeroData[heroCode].AttackFrame2.numberFrame)){
                endCastTime = SDL_GetTicks();
                if(endCastTime - beginCastTime < ATTACKTIME*2){
                    frame -= 1;
                }
                else{
                    Status = MOVEMENT_IDLE;
                    multiAttack = 0;
                    frame = FRAMERESET;
                    return;
                }
            }
            if(multiAttack == 3 and (frame == HeroData[heroCode].AttackFrame1.numberFrame +
                                              HeroData[heroCode].AttackFrame2.numberFrame +
                                              HeroData[heroCode].AttackFrame3.numberFrame)){
                endCastTime = SDL_GetTicks();
                if(endCastTime - beginCastTime < ATTACKTIME*3){
                    frame -= 1;
                }
                else{
                    Status = MOVEMENT_IDLE;
                    multiAttack = 0;
                    frame = FRAMERESET;
                    return;
                }
            }
            updateHitBox(frameWidth,frameHeight);
        }
        else if(Status == MOVEMENT_HURT){
            frame = (frame + 1);
            if(frame == HeroData[heroCode].HurtFrame){
                checkHurt = false;
                Status = MOVEMENT_IDLE;
                return;
            }
        }
        else{
            if ((objectFlag[SDL_SCANCODE_A] and type == 1) or (objectFlag[SDL_SCANCODE_LEFT] and type == 2)) {
                if(Direction != DIRECTION_LEFT){
                    frame = FRAMERESET;
                    Direction = DIRECTION_LEFT;
                    veloX = 0;
                }
                Status = MOVEMENT_MOVE;
                veloX = max(veloX - gravityAccel, (float)-20);
                currentStatus = MOVEMENT_MOVE;
            }
            else if ((objectFlag[SDL_SCANCODE_D] and type == 1) or (objectFlag[SDL_SCANCODE_RIGHT] and type == 2)) {
                if(Direction != DIRECTION_RIGHT){
                    frame = FRAMERESET;
                    Direction = DIRECTION_RIGHT;
                    veloX = 0;
                }
                Status = MOVEMENT_MOVE;
                veloX = min(veloX + gravityAccel, (float)20);
                currentStatus = MOVEMENT_MOVE;
            }
            else{
                Status = MOVEMENT_IDLE;
                currentStatus = MOVEMENT_IDLE;
                veloX = 0;
            }
        }
        Gravity();
        if(Status == MOVEMENT_ATTACK) currentStatus = MOVEMENT_ATTACK;
        else if(Status == MOVEMENT_HURT) currentStatus = MOVEMENT_HURT;
        else{
            if(veloY > 0) currentStatus = MOVEMENT_FALL;
            else if(veloY < 0) currentStatus = MOVEMENT_JUMP;
            frame = (frame + 1)%HeroData[heroCode].TotalFrame;
            xUpdate();
        }
        yUpdate();
        if(Direction == DIRECTION_RIGHT){
            mainBody = {oX + HeroData[heroCode].body.x,oY,HeroData[heroCode].body.w,HeroData[heroCode].body.h};
        }
        else{
            mainBody = {oX + frameWidth - HeroData[heroCode].body.x - HeroData[heroCode].body.w, oY , HeroData[heroCode].body.w,HeroData[heroCode].body.h};
        }
    }
    else{
        currentStatus = Status;
        frame = frame + 1;
        if(frame == HeroData[heroCode].DeadFrame){
            frame -= 1;
        }
    }
    render(oX , oY  , (frame * 250) ,  (currentStatus * 250) , 250, HeroData[heroCode].body.h + HeroData[heroCode].body.y, 1 * (Direction == DIRECTION_LEFT));
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

void Object::updateDirection(int a){
    if(Status != MOVEMENT_IDLE) return;
    if(Direction == DIRECTION_LEFT){
        if(oX < a){
            Direction = DIRECTION_RIGHT;
        }
    }
    if(Direction == DIRECTION_RIGHT){
        if(a < oX){
            Direction = DIRECTION_LEFT;
        }
    }
}

bool Object::loadFromFile(string path){
    deleteObject();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = NULL;

    loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        cout << "Loaded image failed: " << path << endl;
    }
    else{
        SDL_SetColorKey(loadedSurface , SDL_TRUE , SDL_MapRGB(loadedSurface->format, 85, 89, 91 ));//85, 89, 91
//        55595B
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

void Object::deleteObject(){
    if(oTexture != NULL){
        SDL_DestroyTexture(oTexture);
        HP = 100;
        oTexture = NULL;
        oWidth = 0, oHeight = 0;
        Direction = 0;
        veloX = 0.0; veloY = 0.0;
        frame = FRAMERESET;
        Status = 0;
        maxJump = 0;
        checkDoubleJump = false;
        multiAttack = 0;
    }
}


