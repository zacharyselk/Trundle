//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>  // printf is more thread-safe than iostream
#include <common.h>
#include <constants.h>


bool init();
bool loadImg();
void close();

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gSplashScreen = nullptr;

int WinMain( int argc, char* args[] ) {
    if (!init()) {
        DIE("Initalization failed");
    }
    if (!loadImg()) {
        DIE("Image loading failed");
    }

    //Apply the image
    SDL_BlitSurface(gSplashScreen, nullptr, gScreenSurface, nullptr);
    //Update the surface
    SDL_UpdateWindowSurface(gWindow);

    //Wait two seconds
    SDL_Delay(5000);

    close();

    return 0;
}


bool init() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        return false;
    }

    gWindow = SDL_CreateWindow("Trundle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!gWindow) {
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

bool loadImg() {
    gSplashScreen = SDL_LoadBMP("../img/disco_dave.bmp");
    if (!gSplashScreen) {
        return false;
    }

    return true;
}

void close() {
    SDL_FreeSurface(gScreenSurface);
    gScreenSurface = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_Quit();
}