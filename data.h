#ifndef DATA_H
#define DATA_H

#include <string>
#include <SDL.h>
using namespace std;

// HERO LISTS
enum Hero{
    FantasyWarrior,
    SamuraiMartialHero2,
    SamuraiMartialHero,
    TOTAL_HEROS
};

struct skill{
    SDL_Rect hitAOE;
    int numberFrame;
    int dame;
};

struct HeroSpec{
    string filename;
    int TotalFrame;
    int HurtFrame;
    int DeadFrame;
    SDL_Rect body;
    skill AttackFrame1;
    skill AttackFrame2;
    skill AttackFrame3;
};

const HeroSpec HeroData[1] = {
    {"image/FantasyWarrior.png" , 18 , 3 , 7 , {115 , 85 , 30 , 70},
//skill AttackFrame1
        {{90 , 60 , 120 , 110} , 6 , 1},
//skill AttackFrame2
        {{90 , 60 , 120 , 110} , 6 , 1},
//skill AttackFrame3
        {{90 , 60 , 120 , 110} , 10, 2}
    }
//    {"image/SamuraiMartialHero.png", 12 , 6 , 6 ,  0 , {100 , 65 , 133 , 87},  4 , 6, {115 , 86 , 20 , 70}}
};
#endif

