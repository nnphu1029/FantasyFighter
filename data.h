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
    HARASS,
    HP_STEAL,
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
        8 , 3 , 8 , 5 ,  3 , 7 , {107 , 86 , 37 , 70},
        {{102 , 83 , 100 , 67} , 7  , 10 , 4 , NONE},
        {{40 , 62 , 158 , 94} , 14 , 10 , 9 , NONE},
        {{51 , 18 , 162 , 139} , 22 , 15 , 18 , SHIELD_BREAK},
        {{42 , 21 , 171 , 138} , 7  , 10 , 4 , NONE},
        {{44 , 14 , 171 , 143} , 13 , 20, 4 , HP_STEAL}
    },
    {"image/SamuraiRonin.png", "image/ava02.png" , 250 , 250 ,
        8 , 2 , 8 , 5 , 4  , 6 , {109 , 97 , 33 , 55},
        {{108 , 65 , 129 , 89} , 6 , 1 , 4 , NONE},
        {{105 , 86 , 138 , 59} , 12 , 1 , 10 , NONE},
        {{102 , 65 , 135 , 83} , 18 , 2 , 16 , SHIELD_BREAK},
        {{102 , 70 , 135 , 79} , 6 , 2 , 4 , NONE},
        {{106 , 66 , 158 , 80} , 12 , 5, 4 , SHIELD_BREAK}
    },
    {"image/WindAssasin.png" , "image/ava03.png", 563, 250,
       8 , 3 , 6 ,  5 ,   6 , 19  , {267 , 90 , 32 , 75},
        {{242 , 91 , 97 , 55} , 8 , 1 , 2 , NONE},
        {{312 , 75 , 84 , 77} , 18, 1 , 9 , NONE},
        {{324 , 84 , 143 , 80} , 26, 2 , 19 , SHIELD_BREAK},
        {{300 , 43 , 65 , 116} , 8 , 2 , 2 , NONE},
        {{63 , 0 , 500 , 125} , 26, 2 , 0 ,HARASS}
    },
    {"image/FlameKnight.png" , "image/ava04.png" , 563, 250,
       8 , 3 , 7 ,  5 ,   6 , 13  , {262 , 80, 46, 79},
        {{266 , 4 , 149,159} , 9 , 1 , 4 , NONE},
        {{180 , 75 , 251 , 66} , 18, 1 , 10 , NONE},
        {{337 , 34 , 122 , 117} , 25, 2 , 23 , SHIELD_BREAK},
        {{238 , 66 , 227 , 41} , 8 , 2 , 3 , NONE},
        {{345 , 18 , 120 , 145} , 18, 5 , 12 , AIRBORNE}
    },
    {"image/GroundMonk.png" , "image/ava05.png", 563, 250,
       8 , 3 , 6 ,  5 ,   6 , 15  , {290 , 91 , 24 , 68},
        {{313 , 91 , 34 , 38} , 6 , 1 , 2 , NONE},
        {{312 , 91 , 48 , 35} , 12, 1 , 8 , NONE},
        {{354 , 75 , 110 , 83} , 23, 2 , 17 , AIRBORNE},
        {{196 , 62 , 169 , 62} , 7 , 3 , 3 , NONE},
        {{313 , 69 , 81 , 91} , 25, 6 , 5 , HARASS}
    },
    {"image/CrystalMaule.png" , "image/ava06.png", 563, 250,
       8 , 3 , 7 ,  5 ,   6 , 15  , {265 , 82, 35, 75},
        {{231 , 63 , 128, 79} , 7 , 1 , 3 , NONE},
        {{340 , 94 , 37 , 75} , 14, 1 , 10 , NONE},
        {{410 , 57 , 121, 101} , 26, 2 , 17 , SHIELD_BREAK},
        {{294 , 45 , 66 , 109} , 8 , 2 , 3 , NONE},
        {{336 , 32 , 200,125} , 15, 30 , 8 , AIRBORNE}
    },
    {"image/WaterPriestess.png" , "image/ava07.png", 563, 250,
       8 , 3 , 6 ,  5 ,   6 , 16  , {266,92,35,71},
        {{370, 103 , 58 , 25} , 7 , 1 , 3 , NONE},
        {{336, 97 , 112 , 36} , 20 , 1 , 14 , NONE},
        {{385 , 68 , 76 , 95} , 26, 2 , 21 , SHIELD_BREAK},
        {{323,80,121,28} , 8 , 2 , 3 , NONE},
        {{365,3,58,162} , 26, 60 , 11 ,HARASS}
    },
    {"image/MetalBlade.png" , "image/ava08.png", 563, 250,
       8 , 3 , 6 ,  5 ,   6 , 12  , {260 , 80, 33, 67},
        {{283 , 102 , 98 , 29} , 6 , 1 , 1 , NONE},
        {{250 , 100 , 133 , 44} , 9 , 1 , 6 , NONE},
        {{262 , 84 , 124 , 64} , 21, 2 , 11 , HARASS},
        {{325 , 73 , 132 , 41} , 8 , 2 , 2 , NONE},
        {{140 , 59 , 328 , 99} , 11, 6 , 4 ,AIRBORNE}
    },
    {"image/EvilWizard.png" , "image/ava09.png", 250 , 250 ,
        8 , 2 , 8 , 5 ,  3 , 7 , {124, 127, 26 , 53},
        {{171, 37 , 65 , 95} , 8  , 13 , 3 , NONE},
        {{148,33,95,101} , 16 , 1 , 12 , NONE},
        {{171 , 37 , 65 , 95 } , 24 , 15 , 13 , SHIELD_BREAK},
        {{147 , 33 , 101 , 137} , 8  , 10 , 4 , NONE},
        {{0 , 0 ,1200, 600 } , 16 , 5 , 9 , HP_STEAL}
    }
};

#endif

