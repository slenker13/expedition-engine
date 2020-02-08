#include <SDL2/SDL.h>

#include <stdio.h>

#include "Window.hpp"


// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts SDL and initializes window
bool init();

// Frees media and shuts down SDL
void close();

// Game window
Expedition::Window g_window;

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

    SDL_Quit();
}

int main (int argc, char* args[]) {
    // Start up SDL and create window
    if (!init()) {
        printf("ERROR: Failed to initialize.\n");
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
                SDL_SetRenderDrawColor(g_window.getRenderer(), 0xFF, 0x0, 0x0, 0xFF);
                SDL_Rect rect = {g_window.getWidth() / 4, g_window.getHeight() / 4, g_window.getWidth() / 2, g_window.getHeight() / 2};
                SDL_RenderFillRect(g_window.getRenderer(), &rect);

                // Update screen
                g_window.render();
            }
        }
    }

    return 0;
}
