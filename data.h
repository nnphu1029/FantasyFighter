#ifndef DATA_H
#define DATA_H

// CONTAIN INFORMATION , STAT , SKILL , DAME, PLAYER DESIGN

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
    string sound;
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
        {{102 , 83 , 100 , 67} , 7  , 5 , 4 , NONE , "sound/swordslash.wav"},
        {{40 , 62 , 158 , 94} , 14 , 5 , 9 , NONE , "sound/swordslash.wav"},
        {{51 , 18 , 162 , 139} , 22 , 10 , 18 , SHIELD_BREAK , "sound/swordslash.wav"},
        {{42 , 21 , 171 , 138} , 7  , 15 , 4 , NONE , "sound/swordslash.wav"},
        {{44 , 14 , 171 , 143} , 13 , 25 , 4 , HP_STEAL , "sound/Explosion.wav"}
    },
    {"image/SamuraiRonin.png", "image/ava02.png" , 250 , 250 ,
        8 , 2 , 8 , 5 , 4  , 6 , {109 , 97 , 33 , 55},
        {{108 , 65 , 129 , 89} , 6 , 5 , 4 , NONE , "sound/swordslash.wav"},
        {{105 , 86 , 138 , 59} , 12 , 5 , 10 , NONE , "sound/swordslash.wav"},
        {{102 , 65 , 135 , 83} , 18 , 10 , 16 , SHIELD_BREAK , "sound/swordslash.wav"},
        {{102 , 70 , 135 , 79} , 6 , 25 , 4 , NONE , "sound/swordslash.wav"},
        {{106 , 66 , 158 , 80} , 12 , 30 , 4 , SHIELD_BREAK , "sound/swordslash.wav"}
    },
    {"image/WindAssasin.png" , "image/ava03.png", 563, 250,
       8 , 3 , 6 ,  5 ,   6 , 19  , {267 , 90 , 32 , 75},
        {{242 , 91 , 97 , 55} , 8 , 5 , 2 , NONE , "sound/swordslash.wav"},
        {{312 , 75 , 84 , 77} , 18, 5 , 9 , NONE , "sound/swordslash.wav"},
        {{324 , 84 , 143 , 80} , 26, 10 , 19 , SHIELD_BREAK , "sound/swordslash.wav"},
        {{300 , 43 , 65 , 116} , 8 , 15 , 2 , NONE , "sound/swordslash.wav"},
        {{63 , 0 , 500 , 125} , 26, 2 , 0 ,HARASS , "sound/swordslash.wav"}
    },
    {"image/FlameKnight.png" , "image/ava04.png" , 563, 250,
       8 , 3 , 7 ,  5 ,   6 , 13 , {262 , 80, 46, 79},
        {{266 , 4 , 149,159} , 9 , 5 , 4 , NONE , "sound/HeavyWeapon.wav"},
        {{180 , 75 , 251 , 66} , 18, 5 , 10 , NONE , "sound/HeavyWeapon.wav"},
        {{337 , 34 , 122 , 117} , 25, 15 , 23 , SHIELD_BREAK , "sound/Fire.wav"},
        {{238 , 66 , 227 , 41} , 8 , 15 , 3 , NONE , "sound/HeavyWeapon.wav"},
        {{345 , 18 , 120 , 145} , 18, 30 , 12 , AIRBORNE , "sound/Fire.wav"}
    },
    {"image/GroundMonk.png" , "image/ava05.png", 563, 250,
       8 , 3 , 6 ,  5 ,   6 , 15  , {290 , 91 , 24 , 68},
        {{313 , 91 , 34 , 38} , 6 , 5 , 2 , NONE , "sound/Punch.wav"},
        {{312 , 91 , 48 , 35} , 12, 5 , 8 , NONE , "sound/Punch.wav"},
        {{304 , 75 , 160 , 83} , 23, 10 , 17 , AIRBORNE , "sound/Earth.wav"},
        {{196 , 62 , 169 , 62} , 7 , 15 , 3 , NONE , "sound/Punch.wav"},
        {{313 , 69 , 81 , 91} , 25, 4 , 5 , HARASS , "sound/Earth.wav"}
    },
    {"image/CrystalMaule.png" , "image/ava06.png", 563, 250,
       8 , 3 , 7 ,  5 ,   6 , 15  , {265 , 82, 35, 75},
        {{231 , 63 , 128, 79} , 7 , 5 , 3 , NONE , "sound/HeavyWeapon.wav"},
        {{340 , 94 , 37 , 75} , 14, 5 , 10 , NONE , "sound/HeavyWeapon.wav"},
        {{410 , 57 , 121, 101} , 26, 10 , 17 , SHIELD_BREAK , "sound/Explosion.wav"},
        {{294 , 45 , 66 , 109} , 8 , 15 , 3 , NONE , "sound/HeavyWeapon.wav"},
        {{306 , 32 , 230,125} , 15, 25 , 8 , AIRBORNE , "sound/Explosion.wav"}
    },
    {"image/WaterPriestess.png" , "image/ava07.png", 563, 250,
       8 , 3 , 6 ,  5 ,   6 , 16  , {266,92,35,71},
        {{370, 103 , 58 , 25} , 7 , 6 , 3 , NONE ,"sound/daggerSlash.wav"},
        {{336, 97 , 112 , 36} , 20 , 6 , 14 , NONE , "sound/daggerSlash.wav"},
        {{385 , 68 , 76 , 95} , 26, 20 , 21 , AIRBORNE , "sound/daggerSlash.wav"},
        {{323,80,121,28} , 8 , 20 , 3 , NONE , "sound/Water.wav"},
        {{345,3,78,162} , 26, 4 , 11 ,HARASS , "sound/Water.wav"}
    },
    {"image/MetalBlade.png" , "image/ava08.png", 563, 250,
       8 , 3 , 6 ,  5 ,   6 , 12  , {260 , 80, 33, 67},
        {{283 , 102 , 98 , 29} , 6 , 5 , 1 , NONE , "sound/daggerSlash.wav"},
        {{250 , 100 , 133 , 44} , 9 , 5 , 6 , NONE , "sound/daggerSlash.wav"},
        {{262 , 84 , 124 , 64} , 21, 3 , 11 , HARASS ,"sound/daggerSlash.wav"},
        {{325 , 73 , 132 , 41} , 8 , 15 , 2 , NONE , "sound/daggerSlash.wav"},
        {{140 , 59 , 328 , 99} , 11, 20 , 4 ,AIRBORNE , "sound/Explosion.wav"}
    },
    {"image/EvilWizard.png" , "image/ava09.png", 250 , 250 ,
        8 , 2 , 8 , 5 ,  3 , 7 , {124, 127, 26 , 53},
        {{171, 37 , 65 , 95} , 8  , 5 , 3 , NONE , "sound/Explosion.wav"},
        {{148,33,95,101} , 16 , 5 , 12 , NONE , "sound/Explosion.wav"},
        {{171 , 37 , 65 , 95 } , 24 , 10 , 13 , SHIELD_BREAK , "sound/Explosion.wav"},
        {{147 , 33 , 101 , 137} , 8  , 15 , 4 , NONE , "sound/Explosion.wav"},
        {{0 , 0 ,1200, 600 } , 16 , 16 , 9 , HP_STEAL , "sound/Evil.wav"}
    }
};

#endif

