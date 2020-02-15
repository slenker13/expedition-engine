#include "Expedition.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool Expedition::init() {
    // Initialization flag
    bool success = true;

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("ERROR: SDL could not initialize. SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("WARNING: Linear texture filtering not enabled.\n");
        }

        // SDL SUBSYSTEMS
        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            printf("ERROR: SDL_image could not initialize. SDL_image Error: %s\n", IMG_GetError());
            success = false;
        }
    }

    return success;
}

void Expedition::close() {
    IMG_Quit();
    SDL_Quit();
}
