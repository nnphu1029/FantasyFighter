#ifndef const_H
#define const_H

#include<string>
#include<SDL.h>
using namespace std;

// SCREEN SIZE
const int scrWidth = 1200;
const int scrHeight = 600;

// MANAGE FPS
const int TARGET_FPS = 20;
const float TARGET_FRAME_TIME = 1000.0f / TARGET_FPS;
const int OPENINGFRAME = 40;
const int BUTTONFRAME = 20;

// PHYSIC CONSTANT
const float gravityAccel = 3.5f;
const int ATTACKTIME = 400;
const int SPECCOOLDOWN = 500;

// INTIAL DATA
const int PLAYER1X = -200;
const int PLAYERY = scrHeight - 200;
const int PLAYER2X = scrWidth - 300;
const int FRAMERESET = 0;

enum GameState{
    INTRO,
    MENU,
    MAINGAME,
    EXIT,
    OPENING,
    TOTAL_STATE
};



#endif
