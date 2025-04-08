#ifndef OBJECT_H
#define OBJECT_H

//CONTAIN OBJECT FUNCTION

#include <SDL.h>
#include <string>
#include <cstring>
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
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
        int startCooldown , checkCooldown;
        int coolDownShield;
        Mix_Chunk* Attack1;
        Mix_Chunk* Attack2;
        Mix_Chunk* Attack3;
        Mix_Chunk* AirAttack;
        Mix_Chunk* SpAttack;
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
        bool checkIf_I_Win;
        int Status , HP , Direction , limitLeft , limitRight;
// DEFENITE OBJECT
        Object(int);
        void setInitPlayer(int);

// GET FUNCTION
        int getWidth();
        int getHeight();
        SDL_Texture* getTexture();
        int getAttackFrame();

// STATUS FUNCTION
        void Dash();
        void Jump();
        void Attack();
    //ATTACK FUNCTION
        void SpecAttack();
        void castAttack();
    //BLOCK FUNCTION
        void Block();
    //BAD STATUS FUNCTION
        void Hurt(int);
        void AirBorne(int);
        void ShieldBreak(int);
        void Dead();
    //MOVE PROCESS FUNCTION
        void castMoving(int);
        void updateDirection(int , int);
        void movementUpdate(int , int , int);
    //TIME STOP FUNCTION
        void ZA_WARUDO();

//RENDER OBJECT
        void render(int,int,int,int,int,int,int);
// LOADING FUNCTION
        bool loadFromFile(string);
//DELETE OBJECT RESOURCES
        void deleteObject(int);
};
#endif // OBJECT_H
