#ifndef DATA_H
#define DATA_H

#include <string>
#include <SDL.h>
using namespace std;

// PHYSIC CONSTANT
const float gravityAccel = 3.5f;
const int ATTACKTIME = 400;
const int SPECCOOLDOWN = 500;

// INTIAL DATA
const int PLAYERY = scrHeight - 175;
const int FRAMERESET = 0;


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
    int TakeHitframe;
    int effect;
};

enum SkillEffect{
    NONE,
    SHIELD_BREAK,
    ANTI_BLOCK,
    HARASS,
    HP_STEAL,
    STUN,
    TELE,
    AIRBORNE,
    TOTAL_EFFECT
};

struct HeroSpec{
    string filename;
    string avatar;
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
    {"image/FantasyWarrior.png" , "image/ava01.png" , 250 , 250 ,
        8 , 3 , 10 , 10 ,  3 , 7 , {115 , 85 , 30 , 70},
        {{90 , 60 , 120 , 110} , 7  , 1 , 0 , NONE},
        {{90 , 60 , 120 , 110} , 14 , 1 , 0 , NONE},
        {{90 , 60 , 120 , 110} , 22 , 2 , 0 , NONE},
        {{90 , 60 , 120 , 110} , 7  , 2 , 0 , SHIELD_BREAK},
        {{90 , 60 , 120 , 110} , 22 , 60, 0 , HP_STEAL}
    },
    {"image/SamuraiRonin.png", "image/ava02.png" , 250 , 250 ,
        8 , 2 , 8 , 8 , 4  , 6 , {115 , 86 , 20 , 70},
        {{100 , 65 , 133 , 87} , 6 , 1 , 0 , NONE},
        {{100 , 65 , 133 , 87} , 6 , 1 , 0 , NONE},
        {{100 , 65 , 133 , 87} , 6 , 2 , 0 , NONE},
        {{100 , 65 , 133 , 87} , 6 , 2 , 0 , SHIELD_BREAK},
        {{100 , 65 , 133 , 87} , 12 , 5, 0 , TELE}
    },
    {"image/WindAssasin.png" , "image/ava03.png", 563, 250,
       8 , 2 , 6 ,  5 ,   6 , 19  , {115 , 85, 30, 70},
        {{90 , 60 , 120 , 110} , 8 , 1 , 0 , NONE},
        {{90 , 60 , 120 , 110} , 18, 1 , 0 , NONE},
        {{90 , 60 , 120 , 110} , 26, 2 , 0 , NONE},
        {{90 , 60 , 120 , 110} , 8 , 2 , 0 , SHIELD_BREAK},
        {{90 , 60 , 120 , 110} , 26, 60 , 0 ,HARASS}
    },
    {"image/FlameKnight.png" , "image/ava04.png" , 563, 250,
       8 , 2 , 6 ,  5 ,   6 , 13  , {115 , 85, 30, 70},
        {{90 , 60 , 120 , 110} , 8 , 1 , 0 , NONE},
        {{90 , 60 , 120 , 110} , 18, 1 , 0 , NONE},
        {{90 , 60 , 120 , 110} , 26, 2 , 0 , NONE},
        {{90 , 60 , 120 , 110} , 8 , 2 , 0 , SHIELD_BREAK},
        {{90 , 60 , 120 , 110} , 18, 5 , 0 , STUN}
    },

};

#endif

