//Using SDL2 and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>  // printf is more thread-safe than iostream
#include <common.h>
#include <constants.h>
#include <JobPool.h>


int gameLoop(int, char**);
bool init();
bool loadImg();
void close();

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gSplashScreen = nullptr;


// Need to change the entry point name for window
int WinMain(int argc, char* argv[]) {
  return gameLoop(argc, argv);
}
int main(int argc, char* argv[]) {
  return gameLoop(argc, argv);
}

// Main game loop
int gameLoop(int argc, char* argv[]) {
  printf("Starting\n");

  if (!init()) {
    DIE("Initalization failed");
  }
  if (!loadImg()) {
    DIE("Image loading failed");
  }

  bool quit = false;
  SDL_Event event;
  while (!quit) {

    // Handle events
    while (SDL_PollEvent(&event) != 0) {

      // Exit event
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }

  //Apply the image
  SDL_BlitSurface(gSplashScreen, nullptr, gScreenSurface, nullptr);
  //Update the surface
  SDL_UpdateWindowSurface(gWindow);
  }

  close();

  printf("Exiting\n");

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
