#ifndef OBJECT_H
#define OBJECT_H

#include<SDL.h>
#include<string>
#include<iostream>
#include<SDL_image.h>
#include "const.h"
#include "Object.h"
#include "data.h"
using namespace std;

extern SDL_Renderer* gRenderer;

class Object{
    private:
// CONSTANT INDEX
        SDL_Texture* oTexture;
        int oWidth , oHeight , frame , maxJump;
        bool checkDoubleJump;
        int multiAttack;
        bool checkHurt = false;
// UPDATE FUNCTION REQUIRED
        void Gravity();
        void xUpdate();
        void yUpdate();
        void updateHitBox(int , int);
    public:
// PUBLIC INDEX
        int heroCode;
        const Uint8* objectFlag;
        float veloY, veloX;
        int oX , oY;
        SDL_Rect hitbox;
        SDL_Rect mainBody;
        int Status , HP , Direction;
        int beginCastTime , endCastTime;
// GET FUNCTION
        Object(int);
        int getWidth();
        int getHeight();
        int getMultiAttack();
        SDL_Texture* getTexture();
// STATUS FUNCTION
        void Dash();
        void Jump();
        void Attack();
        void Hurt(int);
        void Stun();
        void Dead();
// UPDATE FUNCTION
        void updateDirection(int);
        void movementUpdate(int , int , int);
// LOADING FUNCTION
        bool loadFromFile(string);
        void render(int,int,int,int,int,int,int);
        void deleteObject();
};
#endif // OBJECT_H
