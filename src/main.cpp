#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>

#include "Window.hpp"
#include "Texture.hpp"


// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts SDL and initializes window
bool init();

// Loads media from file
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Game window
Expedition::Window g_window;

// Scene textures
Expedition::Texture g_texture;

bool init() {
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

        // Create window
        if (!g_window.init("Game Window", SCREEN_WIDTH, SCREEN_HEIGHT)) {
            printf("ERROR: Window initialization failed.");
            success = false;
        }
    }

    return success;
}

void close() {
    // Destroy window (destroys renderer)
    g_window.free();

    // Free textures
    g_texture.free();

    IMG_Quit();
    SDL_Quit();
}

bool loadMedia() {
    bool success = true;

    if (!g_texture.loadFromFile("data/smile.png", g_window.getRenderer())) {
        printf("ERROR: Failed to load texture.\n");
        success = false;
    }

    return success;
}

int main (int argc, char* args[]) {
    // Start up SDL and create window
    if (!init()) {
        printf("ERROR: Failed to initialize.\n");
    } else {
        if (!loadMedia()) {
            printf("ERROR: Failed to load media.\n");
        } else {
            // Main look flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // GAME LOOP
            while (!quit) {
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    // Close window
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    g_window.handleEvent(e);
                }

                // Only draw if window is not minimized
                if (!g_window.isMinimized()) {
                    // Clear screen
                    g_window.clearScreen();

                    // Render scene
                    g_texture.render((g_window.getWidth() - g_texture.getWidth()) / 2, (g_window.getHeight() - g_texture.getHeight()) / 2);

                    // Update screen
                    g_window.render();
                }
            }
        }
    }

    return 0;
}
