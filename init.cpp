#include "init.h"


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


void loadMedia(){
    check = true;
    //  LOADING MAIN TEXTURE
        gTexture = loadTexture("image/Bleachst1.png");
        if(gTexture == NULL){
            cout << "Texture Failed" << endl;
            check =  false;
        }

    // LOADING PLAYER1
        P1_HpBar = loadTexture("image/player1_health_bar.png");
        if(P1_HpBar == NULL){
            cout << "Could not load image: " << "image/player1_health_bar.png" << endl;
            check =  false;
        }
        if(!player1.loadFromFile(HeroData[player1.heroCode].filename)){
            cout << "Could not load player1:" << HeroData[player1.heroCode].filename << endl;
            check = false;
        }
        if(!P1_Symbol.loadFromFile("image/P1_icon.png")){
            cout << "Could not load image: " << "image/P1_icon.png" << endl;
            check = false;
        }

    //  LOADING PLAYER2
        P2_HpBar = loadTexture("image/player2_health_bar.png");
        if(P2_HpBar == NULL){
            cout << "Could not load image: " << "image/player2_health_bar.png" << endl;
            check =  false;
        }
        if(!player2.loadFromFile(HeroData[player2.heroCode].filename)){
            cout << "Could not load player2:" << HeroData[player2.heroCode].filename << endl;
            check = false;
        }
        if(!P2_Symbol.loadFromFile("image/P2_icon.png")){
            cout << "Could not load image: " << "image/P2_icon.png" << endl;
            check = false;
        }
    return ;
}

void EndGame(){
    if(gTexture != NULL){
        SDL_DestroyTexture(gTexture);
        gTexture = NULL;
    }
    if(P1_HpBar != NULL){
        SDL_DestroyTexture(P1_HpBar);
        P1_HpBar = NULL;
    }
    if(P2_HpBar != NULL){
        SDL_DestroyTexture(P2_HpBar);
        P2_HpBar = NULL;
    }
    player1.deleteObject();
    player2.deleteObject();

    P1_Symbol.deleteObject();
    P2_Symbol.deleteObject();

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;

    IMG_Quit();
    SDL_Quit();
    return;
}
