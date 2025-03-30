#ifndef DATA_H
#define DATA_H

#include <string>
#include <SDL.h>
using namespace std;

// HERO STATUS
const int MOVEMENT_IDLE = 0;
const int MOVEMENT_MOVE = 1;
const int MOVEMENT_JUMP = 2;
const int MOVEMENT_FALL = 3;

const int MOVEMENT_AIRATTACK = 4;
const int MOVEMENT_DASH = 5;
const int MOVEMENT_ATTACK1 = 6;
const int MOVEMENT_ATTACK2 = 7;
const int MOVEMENT_ATTACK3 = 8;
const int MOVEMENT_SPSKILL = 9;

const int MOVEMENT_BLOCK = 10;
const int MOVEMENT_HURT = 11;
const int MOVEMENT_DEATH = 12;

// HERO DIRECTION
const int DIRECTION_RIGHT = 1;
const int DIRECTION_LEFT = -1;

struct skill{
    SDL_Rect hitAOE;
    int numberFrame;
    int dame;
};

struct HeroSpec{
    string filename;
    int frWidth;
    int frHeight;
    int MovingFrame;
    int JumpFallFrame;
    int DashFrame;
    int BlockFrame;
    int HurtFrame;
    int DeadFrame;
    SDL_Rect body;
    skill AttackFrame1;
    skill AttackFrame2;
    skill AttackFrame3;
    skill AirAttack;
    skill SpecSkill;
};

const HeroSpec HeroData[10] = {
    {"image/FantasyWarrior.png" , 250, 250,
        8 , 3 , 10 , 10 ,  3 , 7 , {115 , 85 , 30 , 70},
        {{90 , 60 , 120 , 110} , 7 , 1},
        {{90 , 60 , 120 , 110} , 14 , 1},
        {{90 , 60 , 120 , 110} , 22 , 2},
        {{90 , 60 , 120 , 110} , 7 , 2},
        {{90 , 60 , 120 , 110} , 22 , 30}
    },
    {"image/SamuraiRonin.png", 250 , 250 ,
        8 , 2 , 8 , 8 , 4  , 6 , {115 , 86 , 20 , 70},
        {{100 , 65 , 133 , 87} , 6 , 1},
        {{100 , 65 , 133 , 87} , 6 , 1},
        {{100 , 65 , 133 , 87} , 6 , 2},
        {{100 , 65 , 133 , 87} , 6 , 2},
        {{100 , 65 , 133 , 87} , 12 , 5}
    },
    {"image/WindAssasin.png" , 563, 250,
       8 , 2 , 6 ,  5 ,   6 , 19  , {115 , 85, 30, 70},
        {{90 , 60 , 120 , 110} , 8 , 1},
        {{90 , 60 , 120 , 110} , 18, 1},
        {{90 , 60 , 120 , 110} , 26, 2},
        {{90 , 60 , 120 , 110} , 8 , 2},
        {{90 , 60 , 120 , 110} , 26, 5}
    },
    {"image/FlameKnight.png" , 563, 250,
       8 , 2 , 6 ,  5 ,   6 , 13  , {115 , 85, 30, 70},
        {{90 , 60 , 120 , 110} , 8 , 1},
        {{90 , 60 , 120 , 110} , 18, 1},
        {{90 , 60 , 120 , 110} , 26, 2},
        {{90 , 60 , 120 , 110} , 8 , 2},
        {{90 , 60 , 120 , 110} , 18, 5}
    },

};
#endif

