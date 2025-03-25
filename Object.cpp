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
        frame = FRAMERESET;
        Direction = DIRECTION_RIGHT * (type == 1) + DIRECTION_LEFT * (type == 2);
    }
}


int Object::getWidth(){ return oWidth;}

int Object::getHeight(){ return oHeight;}

SDL_Texture* Object::getTexture(){ return oTexture;}


void Object::Dash(){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT) return;
    if(Direction == DIRECTION_LEFT){
        veloX = -100;
    }
    else{
        veloX = 100;
    }
    xUpdate();
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
        Status = MOVEMENT_ATTACK;
        if(multiAttack == 1 and HeroLists[heroCode].AttackFrame2 == 0) return;
        if(multiAttack == 2 and HeroLists[heroCode].AttackFrame3 == 0) return;
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

void Object::Hurt(){
    if(Status == MOVEMENT_DEATH or Status == MOVEMENT_HURT) return;
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

void Object::movementUpdate(int frameWidth , int frameHeight, int type){
    int currentStatus = MOVEMENT_IDLE;
    if(Status != MOVEMENT_DEATH){
        if(Status == MOVEMENT_ATTACK){
            frame = frame + 1;
            if(multiAttack == 1 and (frame == HeroLists[heroCode].AttackFrame1)){
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

            if(multiAttack == 2 and (frame == HeroLists[heroCode].AttackFrame1 + HeroLists[heroCode].AttackFrame2)){
                if(HeroLists[heroCode].AttackFrame2 != 0)
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
            if(multiAttack == 3 and (frame == HeroLists[heroCode].AttackFrame1 + HeroLists[heroCode].AttackFrame2 + HeroLists[heroCode].AttackFrame3)){
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
            if(Direction == DIRECTION_RIGHT){
                hitbox = {oX + HeroLists[heroCode].hitAOE.x , oY , HeroLists[heroCode].hitAOE.w , HeroLists[heroCode].hitAOE.h};
            }
            else{
                hitbox = {oX + frameWidth - HeroLists[heroCode].hitAOE.x - HeroLists[heroCode].hitAOE.w, oY , HeroLists[heroCode].hitAOE.w , HeroLists[heroCode].hitAOE.h};
            }
        }
        else if(Status == MOVEMENT_HURT){
            frame = frame + 1;
            if(frame == HeroLists[heroCode].HurtFrame){
                HP -= 1;
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
            frame = (frame + 1)%HeroLists[heroCode].TotalFrame;
            xUpdate();
        }
        yUpdate();
        if(Direction == DIRECTION_RIGHT){
            mainBody = {oX + HeroLists[heroCode].body.x,oY,HeroLists[heroCode].body.w,HeroLists[heroCode].body.h};
        }
        else{
            mainBody = {oX + frameWidth - HeroLists[heroCode].body.x - HeroLists[heroCode].body.w, oY , HeroLists[heroCode].body.w,HeroLists[heroCode].body.h};
        }
    }
    else{
        currentStatus = Status;
        frame = frame + 1;
        if(frame == HeroLists[heroCode].DeadFrame){
            frame -= 1;
        }
    }
    render(oX , oY  , (frame * 250) ,  (currentStatus * 250) , 250, HeroLists[heroCode].body.h + HeroLists[heroCode].body.y, 1 * (Direction == DIRECTION_LEFT));
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

void Object::updateDirection(int a , int b){
    if(Status != MOVEMENT_IDLE) return;
    if(Direction == DIRECTION_LEFT){
        if(oX < a){
            Direction = DIRECTION_RIGHT;
        }
    }
    if(Direction == DIRECTION_RIGHT){
        if(a < oY){
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


