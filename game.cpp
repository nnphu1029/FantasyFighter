#include "game.h"

SDL_Texture* background_Texture = NULL;
SDL_Texture* presentTexture = NULL;
Object player1(1);
Object player2(2);
int orderRender = 1;
Mix_Music* MainGameBackGroundMusic;
Mix_Chunk* button;

void loadingPlayer(){
// SET UP ZOOM TEXTURE
    presentTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, scrWidth, scrHeight);
// LOADING PLAYER1
    P1_ava = loadTexture(HeroData[player1.heroCode].avatar);
    if(P1_ava == NULL){
        cout << "Could not load image: " << HeroData[player1.heroCode].avatar << endl;
        return;
    }
    P1_HpBar = loadTexture("image/player1_health_bar.png");
    if(P1_HpBar == NULL){
        cout << "Could not load image: " << "image/player1_health_bar.png" << endl;
        return;
    }
    if(!player1.loadFromFile(HeroData[player1.heroCode].filename)){
        cout << "Could not load player1:" << HeroData[player1.heroCode].filename << endl;
        return;
    }
    if(!P1_Symbol.loadFromFile("image/P1_icon.png")){
        cout << "Could not load image: " << "image/P1_icon.png" << endl;
        return;
    }

//  LOADING PLAYER2
    P2_ava = loadTexture(HeroData[player2.heroCode].avatar);
    if(P2_ava == NULL){
        cout << "Could not load image: " << HeroData[player2.heroCode].avatar << endl;
        return;
    }
    P2_HpBar = loadTexture("image/player2_health_bar.png");
    if(P2_HpBar == NULL){
        cout << "Could not load image: " << "image/player2_health_bar.png" << endl;
        return;
    }
    if(!player2.loadFromFile(HeroData[player2.heroCode].filename)){
        cout << "Could not load player2:" << HeroData[player2.heroCode].filename << endl;
        return;
    }
    if(!P2_Symbol.loadFromFile("image/P2_icon.png")){
        cout << "Could not load image: " << "image/P2_icon.png" << endl;
        return;
    }
    player1.setInitPlayer(1);
    player2.setInitPlayer(2);

    int backgroundMusicCode = rand()%5;
    MainGameBackGroundMusic = Mix_LoadMUS(mapsound[backgroundMusicCode].c_str());
    if (!MainGameBackGroundMusic) {
        cout << "Could not load Main game music" << endl;
        return;
    }
    else{
        Mix_PlayMusic(MainGameBackGroundMusic, -1);
    }
    return;
}

void mainGame(){
    SDL_RenderClear(gRenderer);

    loadingPlayer();

    bool quitGame = false;
    CheckPause = false;
    Winner = -1;

    while(!quitGame){
        currentFrameTime = SDL_GetTicks();
        SDL_SetRenderTarget(gRenderer,presentTexture);

        SDL_RenderClear(gRenderer);

        SDL_RenderCopy(gRenderer,background_Texture,NULL,NULL);

        while(SDL_PollEvent(&FantasyFighter) != 0){
            if(FantasyFighter.type == SDL_QUIT){
                quitGame = true;
                quitFantasyFighter = true;
                continue;
            }
            if(FantasyFighter.type == SDL_KEYDOWN){
                if(Winner != -1){
                    Mix_PlayChannel(-1, button, 0);
                    VictoryKeyPressProcess(quitGame);
                }
                else{
                    if(CheckPause == true){
                        Mix_PlayChannel(-1, button, 0);
                        PauseKeyPressProcess(quitGame);
                    }
                    else{
                        mainGameKeyPressProcess();
                    }
                }
            }
        }
        if(Winner == -1){
            player1.objectFlag = SDL_GetKeyboardState(NULL);
            player2.objectFlag = SDL_GetKeyboardState(NULL);
        }
        if(CheckPause == true){
            player1.ZA_WARUDO();
            player2.ZA_WARUDO();
        }
        else{
            if(orderRender == 1){
                player1.movementUpdate(HeroData[player1.heroCode].frWidth , HeroData[player1.heroCode].frHeight , 1);
                player2.movementUpdate(HeroData[player2.heroCode].frWidth , HeroData[player2.heroCode].frHeight , 2);
            }
            else{
                player2.movementUpdate(HeroData[player2.heroCode].frWidth , HeroData[player2.heroCode].frHeight , 2);
                player1.movementUpdate(HeroData[player1.heroCode].frWidth , HeroData[player1.heroCode].frHeight , 1);
            }
        }

        interactProcess();
        updateDetails();
        if(Winner == -1){
            if(CheckPause == true){
                renderPause();
            }
        }
        else{
            renderVictory();
        }
// PRESENT RENDERER
        SDL_RenderPresent(gRenderer);
// MANAGE FPS
        frameTime = SDL_GetTicks() - currentFrameTime;
        if (frameTime < TARGET_FRAME_TIME) {
            SDL_Delay(TARGET_FRAME_TIME - frameTime);
        }
    }
    closeMainGame();
    if(quitFantasyFighter != true){
        renderOpening();
    }
    return;
}

void mainGameKeyPressProcess(){
    switch (FantasyFighter.key.keysym.sym){
        case SDLK_ESCAPE:
            CheckPause = true; break;
        case(SDLK_j):
            player1.Attack(); break;
        case(SDLK_w):
            player1.Jump(); break;
        case(SDLK_l):
            player1.Dash(); break;
        case(SDLK_s):
            player1.Block(); break;
        case(SDLK_u):
            player1.SpecAttack();break;

        case(SDLK_KP_4):
            player2.Attack(); break;
        case(SDLK_UP):
            player2.Jump(); break;
        case(SDLK_KP_6):
            player2.Dash(); break;
        case(SDLK_DOWN):
            player2.Block(); break;
        case (SDLK_KP_7):
            player2.SpecAttack(); break;
        case SDLK_t:
            player1.HP = 0;
            player2.HP = 0; break;
    }
}

void updateDetails(){
    SDL_RenderCopy(gRenderer,presentTexture,NULL,NULL);
    SDL_SetRenderTarget(gRenderer,NULL);
    updateZoom();
    if(Winner == -1 and quitFantasyFighter != true){
        renderAvatar(1);
        renderAvatar(2);
        renderHPBar(100 - player1.HP , 1);
        renderHPBar(100 - player2.HP , 2);
    }
}

void closeMainGame(){
    Mix_FreeMusic(MainGameBackGroundMusic);
    MainGameBackGroundMusic = NULL;

    SDL_DestroyTexture(presentTexture);
    presentTexture = NULL;
    SDL_DestroyTexture(background_Texture);
    background_Texture = NULL;

    SDL_DestroyTexture(P1_ava);
    P1_ava = NULL;
    SDL_DestroyTexture(P1_HpBar);
    P1_HpBar = NULL;
    player1.deleteObject(1);
    P1_Symbol.deleteObject(0);

    SDL_DestroyTexture(P2_HpBar);
    P2_HpBar = NULL;
    player2.deleteObject(2);
    SDL_DestroyTexture(P2_ava);
    P2_ava = NULL;
    P2_Symbol.deleteObject(0);
}
