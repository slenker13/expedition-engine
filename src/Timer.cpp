#include "Timer.hpp"

#include <SDL2/SDL_timer.h>

Expedition::Timer::Timer() {
    m_startTicks = 0;
    m_pausedTicks = 0;

    m_started = false;
    m_paused = false;
}

void Expedition::Timer::start() {
    // Start the timer
    m_started = true;

    // Unpause the timer
    m_paused = false;

    // Get current clock ticks
    m_startTicks = SDL_GetTicks();
    m_pausedTicks = 0;
}

void Expedition::Timer::stop() {
    // Stop the timer
    m_started = false;

    // Unpause the timer
    m_paused = false;

    // Clear tick variables
    m_startTicks = 0;
    m_pausedTicks = 0;
}

void Expedition::Timer::pause() {
    if (m_started && !m_paused) {
        // Pause timer
        m_paused = true;

        // Calculate paused ticks
        m_pausedTicks = SDL_GetTicks() - m_startTicks;
        m_startTicks = 0;
    }
}

void Expedition::Timer::unpause() {
    if (m_started && m_paused) {
        // Unpause timer
        m_paused = false;

        // Reset starting ticks
        m_startTicks = SDL_GetTicks() - m_pausedTicks;

        // Reset paused ticks
        m_pausedTicks = 0;
    }
}

uint32_t Expedition::Timer::getTicks() {
    // Timer time
    uint32_t time = 0;

    // If started
    if (m_started) {
        // If paused
        if (m_paused) {
            // Return number of ticks when timer was paused
            time = m_pausedTicks;
        } else {
            // Return current time minus start time
            time = SDL_GetTicks() - m_startTicks;
        }
    }

    return time;
}

bool Expedition::Timer::isStarted() {
    return m_started;
}

bool Expedition::Timer::isPaused() {
    return m_paused && m_started;
}
