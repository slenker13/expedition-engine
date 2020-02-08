#include "Window.hpp"

#include <SDL2/SDL_events.h>

Expedition::Window::Window() {
    // Initialize window
    m_window = nullptr;
    m_renderer = nullptr;

    m_mouseFocus = false;
    m_keyboardFocus = false;
    m_fullScreen = false;
    m_minimized = false;
    m_shown = false;

    m_width = 0;
    m_height = 0;
}

bool Expedition::Window::init(std::string name, int width, int height) {
    // Success flag
    bool success = true;

    // Create window
    // TODO: Option of windowed/fullscreen? Fullscreen all the time?
    m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (m_window == nullptr) {
        printf("ERROR: Window could not be created. SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        m_mouseFocus = true;
        m_keyboardFocus = true;
        m_width = width;
        m_height = height;

        // Create renderer
        // TODO: VSYNC optional
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (m_renderer == nullptr) {
            printf("ERROR: Renderer could not be created. SDL Error: %s\n", SDL_GetError());
            SDL_DestroyWindow(m_window);
            success = false;
        } else {
            // Init draw color
            SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

            // Focus window
            focus();
            m_shown = true;
        }
    }

    return success;
}

void Expedition::Window::free() {
    if (m_renderer != nullptr) {
        SDL_DestroyRenderer(m_renderer);
    }
    if (m_window != nullptr) {
        SDL_DestroyWindow(m_window);
    }

    m_mouseFocus = false;
    m_keyboardFocus = false;
    m_fullScreen = false;
    m_minimized = false;
    m_shown = false;
    
    m_width = 0;
    m_height = 0;
}

void Expedition::Window::handleEvent(SDL_Event& e) {
    // Window event occured
    if (e.type == SDL_WINDOWEVENT) {
        switch (e.window.event) {
            // Get new dimensions and repaint on window size change
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                m_width = e.window.data1;
                m_height = e.window.data2;
                SDL_RenderPresent(m_renderer);
            break;

            // Repaint on exposure
            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent(m_renderer);
            break;

            // Mouse entered window
            case SDL_WINDOWEVENT_ENTER:
                m_mouseFocus = true;
            break;

            // Mouse left window
            case SDL_WINDOWEVENT_LEAVE:
                m_mouseFocus = false;
            break;

            // Window has keyboard focus
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                m_keyboardFocus = true;
            break;

            // Window lost keyboard focus
            case SDL_WINDOWEVENT_FOCUS_LOST:
                m_keyboardFocus = false;
            break;

            // Window minimized
            case SDL_WINDOWEVENT_MINIMIZED:
                m_minimized = true;
            break;

            // Window maximized
            case SDL_WINDOWEVENT_MAXIMIZED:
                m_minimized = false;
            break;

            // Window restored
            case SDL_WINDOWEVENT_RESTORED:
                m_minimized = false;
            break;

            // Window appeared
            case SDL_WINDOWEVENT_SHOWN:
                m_shown = true;
            break;

            // Window disappeared 
            case SDL_WINDOWEVENT_HIDDEN:
                m_shown = false;
            break;
        }
    }
}

void Expedition::Window::focus() {
    // Restore if needed
    if (!m_shown) {
        SDL_ShowWindow(m_window);
    }

    // Move to front
    SDL_RaiseWindow(m_window);
}

void Expedition::Window::clearScreen() {
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(m_renderer);
}

void Expedition::Window::render() {
    SDL_RenderPresent(m_renderer);
}

SDL_Renderer* Expedition::Window::getRenderer() {
    return m_renderer;
}

int Expedition::Window::getWidth() {
    return m_width;
}

int Expedition::Window::getHeight() {
    return m_height;
}

bool Expedition::Window::hasMouseFocus() {
    return m_mouseFocus;
}

bool Expedition::Window::hasKeyboardFocus() {
    return m_keyboardFocus;
}

bool Expedition::Window::isFullscreen() {
    return m_fullScreen;
}

bool Expedition::Window::isMinimized() {
    return m_minimized;
}

bool Expedition::Window::isShown() {
    return m_shown;
}
