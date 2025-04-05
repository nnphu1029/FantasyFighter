#include "menu.h"

SDL_Texture* P1_SelectHero = NULL;
SDL_Texture* P2_SelectHero = NULL;
SDL_Texture* SelectMap = NULL;

void initMenu(){
    check = true;
    background_Texture = loadTexture("image/menu.png");
    if(background_Texture == NULL){
        cout << "Load Texture Failed: " << "image/menu.png" << endl;
        check = false;
        return;
    }
    P1_SelectHero = loadTexture("image/select1.png");
    if(P1_SelectHero == NULL){
        cout << "Load Texture Failed: " << "P1_SelectHero" << endl;
        check = false;
        return;
    }
    P2_SelectHero = loadTexture("image/select2.png");
    if(P2_SelectHero == NULL){
        cout << "Load Texture Failed: " << "P2_SelectHero" << endl;
        check = false;
        return;
    }
    SelectMap = loadTexture("image/SelectMap.png");
    if(SelectMap == NULL){
        cout << "Load Texture Failed: " << "SelectMap" << endl;
        check = false;
        return;
    }
}

void RenderMenu(){
    SDL_RenderClear(gRenderer);
    initMenu();
    if(check == false){
        cout << "Init Menu Failed" << endl;
        return;
    }

    bool checkPlayer1Select = false;
    bool checkPlayer2Select = false;
    bool checkMapSelect = false;
    bool quitMenu = false;

    int P1_Slot = 0;
    int P2_Slot = 0;
    int Map_Slot = 0;

    while(!quitMenu){
        currentFrameTime = SDL_GetTicks();

        while(SDL_PollEvent(&FantasyFighter) != 0){
            if(FantasyFighter.type == SDL_QUIT){
                quitMenu = true;
                quitFantasyFighter = true;
                continue;
            }
            if(FantasyFighter.type == SDL_KEYDOWN){
                if(CheckPause == true){
                    switch(FantasyFighter.key.keysym.sym){
                        case SDLK_UP:
                            PauseMenuState = min(PauseMenuState - 1 , 0);
                            break;
                        case SDLK_DOWN:
                            PauseMenuState = max(PauseMenuState + 1 , 1);
                            break;
                        case SDLK_RETURN:
                            switch (PauseMenuState){
                                case 0:
                                    CheckPause = false;
                                    break;
                                case 1:
                                    CheckPause = false;
                                    quitMenu = true;
                                    quitFantasyFighter = true;
                                    break;
                            }
                        break;
                    }
                }
                else{
                    if(checkPlayer1Select == false){
                        switch (FantasyFighter.key.keysym.sym){
                            case SDLK_ESCAPE:
                                CheckPause = true;
                                break;
                            case SDLK_w:
                                P1_Slot = max((P1_Slot - 3),0);
                                break;
                            case SDLK_s:
                                P1_Slot = min((P1_Slot + 3),9);
                                break;
                            case SDLK_d:
                                P1_Slot = min((P1_Slot + 1),9);
                                break;
                            case SDLK_a:
                                P1_Slot = max((P1_Slot - 1),0);
                                break;
                            case SDLK_j:
                                checkPlayer1Select = true;
                                player1.heroCode = P1_Slot;
                                break;
                        }
                    }
                    else if(checkPlayer2Select == false){
                        switch (FantasyFighter.key.keysym.sym){
                            case SDLK_ESCAPE:
                                CheckPause = true;
                                break;
                            case SDLK_UP:
                                if(checkPlayer1Select == false) break;
                                P2_Slot = max((P2_Slot - 3),0);
                                break;
                            case SDLK_DOWN:
                                if(checkPlayer1Select == false) break;
                                P2_Slot = min((P2_Slot + 3),9);
                                break;
                            case SDLK_RIGHT:
                                if(checkPlayer1Select == false) break;
                                P2_Slot = min((P2_Slot + 1),9);
                                break;
                            case SDLK_LEFT:
                                if(checkPlayer1Select == false) break;
                                P2_Slot = max((P2_Slot - 1),0);
                                break;
                            case SDLK_KP_4:
                                if(checkPlayer1Select == false) break;
                                checkPlayer2Select = true;
                                player2.heroCode = P2_Slot;
                                break;
                        }
                    }
                    else if(checkMapSelect == false){
                        switch (FantasyFighter.key.keysym.sym){
                            case SDLK_ESCAPE:
                                CheckPause = true;
                                break;
                            case SDLK_w:
                                if(checkPlayer2Select == false) break;
                                Map_Slot = max((Map_Slot - 2),0);
                                break;
                            case SDLK_s:
                                if(checkPlayer2Select == false) break;
                                Map_Slot = min((Map_Slot + 2),6);
                                break;
                            case SDLK_d:
                                if(checkPlayer2Select == false) break;
                                Map_Slot = min((Map_Slot + 1),6);
                                break;
                            case SDLK_a:
                                if(checkPlayer2Select == false) break;
                                Map_Slot = max((Map_Slot - 1),0);
                                break;
                            case SDLK_KP_4:
                                if(checkPlayer2Select == false) break;
                                checkMapSelect = true;
                                break;
                        }
                    }
                }
            }
        }
        if(checkPlayer1Select == true and checkPlayer2Select == true and checkMapSelect == true){
            quitMenu = true;
            currentState = MAINGAME;
            continue;
        }
        SDL_RenderCopy(gRenderer,background_Texture,NULL,NULL);

        SDL_RenderCopy(gRenderer,P1_SelectHero,NULL,&menuHero[P1_Slot]);

        if(checkPlayer1Select == true){
            SDL_RenderCopy(gRenderer,P2_SelectHero,NULL,&menuHero[P2_Slot]);
        }
        if(checkPlayer2Select == true){
            SDL_RenderCopy(gRenderer,SelectMap,NULL,&menuMap[Map_Slot]);
        }
        if(CheckPause == true){
            renderPause();
        }

        SDL_RenderPresent(gRenderer);

        frameTime = SDL_GetTicks() - currentFrameTime;
        if (frameTime < TARGET_FRAME_TIME) {
            SDL_Delay(TARGET_FRAME_TIME - frameTime);
        }
    }
    closeMenu();
    if(quitFantasyFighter != true){
        renderOpening();
        loadingMap(Map_Slot);
        if(player1.heroCode == 9){
            player1.heroCode = rand() % 8;
        }
        if(player2.heroCode == 9){
            player2.heroCode = rand() % 8;
        }
    }
    return;
}

void loadingMap(int code){
    if(code == 6){
        code = rand() % 5;
    }
    background_Texture = loadTexture(MapCode[code]);
    if(background_Texture == NULL){
        cout << "Texture Failed" << endl;
        return;
    }
}

void closeMenu(){
    SDL_DestroyTexture(background_Texture);
    background_Texture = NULL;

    SDL_DestroyTexture(P1_SelectHero);
    P1_SelectHero = NULL;

    SDL_DestroyTexture(P2_SelectHero);
    P2_SelectHero = NULL;

    SDL_DestroyTexture(SelectMap);
    SelectMap = NULL;
}
