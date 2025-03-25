#ifndef const_H
#define const_H
#include <SDL.h>
#include<string>
using namespace std;

// SCREEN SIZE
const int scrWidth = 1200;
const int scrHeight = 600;

// MANAGE FPS
const int TARGET_FPS = 20;
const float TARGET_FRAME_TIME = 1000.0f / TARGET_FPS;
const int OPENINGFRAME = 40;

// PHYSIC CONSTANT
const float gravityAccel = 3.5f;
const int ATTACKTIME = 400;

// INTIAL DATA
const int PLAYER1X = 0;
const int PLAYERY = scrHeight - 200;
const int PLAYER2X = scrWidth - 250;
const int FRAMERESET = -1;
const int FRAME_SIZE = 250;

// HERO STATUS
const int MOVEMENT_IDLE = 0;
const int MOVEMENT_MOVE = 1;
const int MOVEMENT_ATTACK = 2;
const int MOVEMENT_JUMP = 3;
const int MOVEMENT_FALL = 4;
const int MOVEMENT_HURT = 5;
const int MOVEMENT_DEATH = 6;


// HERO DIRECTION
const int DIRECTION_RIGHT = 1;
const int DIRECTION_LEFT = -1;

// HERO LISTS
enum Hero{
    FantasyWarrior,
    SamuraiMartialHero2,
    SamuraiMartialHero,
    TOTAL_HEROS
};

enum GameState{
    INTRO,
    MENU,
    OPENING,
    MAINGAME,
    EXIT,
    TOTAL_STATE
};

struct HeroInfo{
    string filename;
    int TotalFrame;
    int AttackFrame1;
    int AttackFrame2;
    int AttackFrame3;
    SDL_Rect hitAOE;
    int HurtFrame;
    int DeadFrame;
    SDL_Rect body;
};

const HeroInfo HeroLists[TOTAL_HEROS - 1] = {
    {"image/FantasyWarrior.png" , 18 , 6 , 6 , 10 , {90 , 60 , 120 , 110}  , 3 , 6 , {115 , 85 , 30 , 70}},
//    {"image/SamuraiMartialHero2.png" , 8 , 4 , 4 , 0 , 3 , 6},
    {"image/SamuraiMartialHero.png", 12 , 6 , 6 ,  0 , {100 , 65 , 133 , 87},  4 , 6, {115 , 86 , 20 , 70}}
};

#endif
