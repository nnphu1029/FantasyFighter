#ifndef const_H
#define const_H

// CONTAIN GAME CONSTANT LIKE GRAVITY , ACCEL , NUMBER FRAMES OF A BUTTON,...

#include<string>
#include<SDL.h>
using namespace std;

// SCREEN SIZE
const int scrWidth = 1200;
const int scrHeight = 600;

// MANAGE FPS
const int TARGET_FPS = 20;
const float TARGET_FRAME_TIME = 1000.0f / TARGET_FPS;


// BASIC FRAME'S INFORMATION
const int OPENINGFRAME = 40;
const int BUTTONFRAME = 20;
const int FRAMEHEIGHT = 250;

enum GameState{
    INTRO,
    MENU,
    MAINGAME,
    OPENING,
    TOTAL_STATE
};

const string MapCode[7] = {
    "image/map_1.png",
    "image/map_2.png",
    "image/map_3.png",
    "image/map_4.png",
    "image/map_5.png",
    "image/map_6.png"
};

const string mapsound[7] = {
    "sound/mapsound1.ogg",
    "sound/mapsound2.ogg",
    "sound/mapsound3.ogg",
    "sound/mapsound4.ogg",
    "sound/mapsound5.ogg"
};

const SDL_Rect menuHero[10] = {
    {155,50,108,125} , {290,50,108,125} , {405,50,108,125},
    {155,190,108,125} , {290,190,108,125} , {405,190,108,125},
    {155,330,108,125} , {290,330,108,125} , {405,330,108,125} ,
    {155,445,108,125}
};

const SDL_Rect menuMap[7] = {
    {601,41,210,141}  , {824,41,210,141},
    {601,184,210,141} , {824,184,210,141},
    {601,324,210,141} , {824,324,210,141},
                        {824,454,210,141}
};

#endif //DATA_H
