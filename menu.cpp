#include "menu.h"

void initMenu(){
    gTexture = loadTexture("image/menu.png");
    if(gTexture == NULL){
        cout << "Load Texture Failed: " << "image/menu.png" << endl;
        return;
    }
    P1_SelectHero = loadTexture("image/select1.png");
    if(P1_SelectHero == NULL){
        cout << "Load Texture Failed: " << "P1_SelectHero" << endl;
        return;
    }
    P2_SelectHero = loadTexture("image/select2.png");
    if(P2_SelectHero == NULL){
        cout << "Load Texture Failed: " << "P2_SelectHero" << endl;
        return;
    }
}

void RenderMenu(){
    SDL_RenderClear(gRenderer);
    initMenu();
    bool checkPlayer1Select = false;
    bool checkPlayer2Select = false;
    bool checkMapSelect = false;
    bool quitMenu = false;
    int P1_Slot = 0;
    int P2_Slot = 0;
    int currentFrameTime, frameTime;
    while(!quitMenu){
        currentFrameTime = SDL_GetTicks();
        SDL_RenderCopy(gRenderer,gTexture,NULL,NULL);
        while(SDL_PollEvent(&FantasyFighter) != 0){
            if(FantasyFighter.type == SDL_QUIT){
                quitMenu = true;
                quitFantasyFighter = true;
                continue;
            }
            if(FantasyFighter.type == SDL_KEYDOWN){
                switch (FantasyFighter.key.keysym.sym){
                    case SDLK_ESCAPE:
                        quitMenu = true;
                        quitFantasyFighter = true;
                        break;
                    case SDLK_w:
                        P1_Slot = max((P1_Slot - 3),0);
                        break;
                    case SDLK_s:
                        P1_Slot = min((P1_Slot + 3),8);
                        break;
                    case SDLK_d:
                        P1_Slot = min((P1_Slot + 1),8);
                        break;
                    case SDLK_a:
                        P1_Slot = max((P1_Slot - 1),0);
                        break;
                    case SDLK_j:
                        checkPlayer1Select = true;
                        break;

                    case SDLK_UP:
                        P2_Slot = max((P2_Slot - 3),0);
                        break;
                    case SDLK_DOWN:
                        P2_Slot = min((P2_Slot + 3),8);
                        break;
                    case SDLK_RIGHT:
                        P2_Slot = min((P2_Slot + 1),8);
                        break;
                    case SDLK_LEFT:
                        P2_Slot = max((P2_Slot - 1),0);
                        break;
                    case SDLK_KP_4:
                        checkPlayer2Select = true;
                        break;
                }
            }
        }
        if(checkPlayer1Select == true and checkPlayer2Select == true){
            quitMenu = true;
            currentState = OPENING;
            continue;
        }
        if(checkPlayer1Select == false){
            SDL_RenderCopy(gRenderer,P1_SelectHero,NULL,&menuHero[P1_Slot]);
            player1.heroCode = P1_Slot;
        }
        else{
            SDL_DestroyTexture(P1_SelectHero);
            P1_SelectHero = NULL;
            if(checkPlayer2Select == false){
                SDL_RenderCopy(gRenderer,P2_SelectHero,NULL,&menuHero[P2_Slot]);
                player2.heroCode = P2_Slot;
            }
            else{
                SDL_DestroyTexture(P2_SelectHero);
                P2_SelectHero = NULL;
            }
        }
        SDL_RenderPresent(gRenderer);
        frameTime = SDL_GetTicks() - currentFrameTime;
        if (frameTime < TARGET_FRAME_TIME) {
            SDL_Delay(TARGET_FRAME_TIME - frameTime);
        }
    }
    closeMenu();
    return;
}

void closeMenu(){
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    SDL_DestroyTexture(P1_SelectHero);
    P1_SelectHero = NULL;

    SDL_DestroyTexture(P2_SelectHero);
    P2_SelectHero = NULL;
}
