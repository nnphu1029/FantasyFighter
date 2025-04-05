#include "init.h"

SDL_Window* window = NULL;
SDL_Renderer* gRenderer = NULL;
bool check = false;

void Init(){
    check = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "Warning: SDL_INIT_VIDEO ERROR!" << endl;
        check = false;
    }
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )){
        cout << "Warning: Linear texture filtering not enabled!" << endl;
        check = false;
    }
    window = SDL_CreateWindow("FANTASY FIGHTER",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              scrWidth,scrHeight,SDL_WINDOW_SHOWN);
    if(window == NULL){
        cout << "Warning: Created Window failed" << endl;
        check = false;
    }
    gRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(gRenderer == NULL){
        cout << "Renderer Error! SDL_image Error: %s\n!" << endl;
        check = false;
    }
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) and imgFlags)){
        cout << "PNG INIT Error! SDL_image Error: %s\n!" << endl;
        check = false;
    }
    return;
}


SDL_Texture* loadTexture(string path){
	SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if( loadedSurface == NULL ){
		cout << "Unabled to upload image!" << endl;
	}
    newTexture = SDL_CreateTextureFromSurface(gRenderer,loadedSurface);
    if(newTexture == NULL ){
        cout << "Created Texure failed: newTexure" << endl;
    }
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

void EndGame(){
    SDL_DestroyTexture(background_Texture);
    background_Texture = NULL;
    SDL_DestroyTexture(P1_HpBar);
    P1_HpBar = NULL;
    SDL_DestroyTexture(P2_HpBar);
    P2_HpBar = NULL;

    SDL_DestroyTexture(P1_SelectHero);
    P1_SelectHero = NULL;

    SDL_DestroyTexture(P2_SelectHero);
    P2_SelectHero = NULL;

    player1.deleteObject(1);
    player2.deleteObject(2);

    P1_Symbol.deleteObject(0);
    P2_Symbol.deleteObject(0);

    SDL_DestroyTexture(PauseTexture);
    PauseTexture = NULL;
    QuitGameButton.deleteObject(0);
    ResumeButton.deleteObject(0);
    MenuButton.deleteObject(0);

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
    return;
}
