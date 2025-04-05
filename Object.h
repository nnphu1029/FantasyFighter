#ifndef OBJECT_H
#define OBJECT_H

#include<SDL.h>
#include<string>
#include<iostream>
#include<SDL_image.h>
#include "const.h"
#include "data.h"
using namespace std;

extern SDL_Renderer* gRenderer;

class Object{
    private:
// CONSTANT INDEX
        SDL_Texture* oTexture;
        int oWidth , oHeight , frame , maxJump;
        bool checkDoubleJump;
        bool checkHurt;
        bool checkAttack;
        bool checkAirBorne;
        int beginCastTime , endCastTime;
        int startCooldown , checkCooldown ;
// UPDATE FUNCTION REQUIRED
        void Gravity();
        void xUpdate();
        void yUpdate();
        void updateMainBody(int , int);
        void updateHitBox(int , int);
    public:
// PUBLIC INDEX
        int heroCode;
        const Uint8* objectFlag;
        float veloY, veloX;
        int oX , oY;
        SDL_Rect hitbox;
        SDL_Rect mainBody;
        int Status , HP , Direction , limitLeft , limitRight;
// GET FUNCTION
        Object(int);
        int getWidth();
        int getHeight();
        SDL_Texture* getTexture();
        int getAttackFrame();
        int updateMaxJump(int);
        void setInitLocate(int);
// STATUS FUNCTION
        void Dash();
        void Jump();
        void Attack();
        void SpecAttack();
        void castAttack();
        void Block();
        void Hurt(int);
        void AirBorne();
        void Dead();
        void castMoving(int);
// UPDATE FUNCTION
        void updateDirection(int , int);
        void movementUpdate(int , int , int);
        void ZA_WARUDO();
// LOADING FUNCTION
        bool loadFromFile(string);
        void render(int,int,int,int,int,int,int);
        void deleteObject(int);
};
#endif // OBJECT_H
