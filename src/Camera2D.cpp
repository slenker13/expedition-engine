#include "Camera2D.hpp"

Expedition::Camera2D::Camera2D(int x, int y, int screenWidth, int screenHeight, int levelWidth, int levelHeight) {
    m_cameraRect->x = x;
    m_cameraRect->y = y;
    m_cameraRect->w = screenWidth;
    m_cameraRect->h = screenHeight;

    m_levelWidth = levelWidth;
    m_levelHeight = levelHeight;
}

void Expedition::Camera2D::updatePosition(int x, int y) {
    // Set camera position
    m_cameraRect->x = x;
    m_cameraRect->y = y;

    // Keep camera in bounds
    if (m_cameraRect->x < 0) {
        m_cameraRect->x = 0;
    }
    if (m_cameraRect->y < 0) {
        m_cameraRect->y = 0;
    }
    if (m_cameraRect->x > m_levelWidth - m_cameraRect->w) {
        m_cameraRect->x = m_levelWidth - m_cameraRect->w;
    }
    if (m_cameraRect->y > m_levelHeight - m_cameraRect->h) {
        m_cameraRect->y = m_levelHeight - m_cameraRect->h;
    }
}

SDL_Rect* Expedition::Camera2D::getCameraRect() { return m_cameraRect; }
