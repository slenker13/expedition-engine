#include "Texture.hpp"

#include <SDL2/SDL_image.h>

Expedition::Texture::Texture() {
    // Initialize
    m_texture = nullptr;
    m_renderer = nullptr;
    m_width = 0;
    m_height = 0;
}

Expedition::Texture::~Texture() {
    // Deallocate
    free();
}

bool Expedition::Texture::loadFromFile(std::string path, SDL_Renderer* renderer) {
    // Free existing texture
    free();

    // Load image at path
    SDL_Surface* imageSurface = IMG_Load(path.c_str());
    if (imageSurface == nullptr) {
        printf("ERROR: Unable to load image %s. SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        // Color key image
        SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format, 0x00, 0xFF, 0xFF));

        // Create texture from surface
        m_texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        if (m_texture == nullptr) {
            printf("ERROR: Unable to create texture from %s. SDL Error: %s", path.c_str(), SDL_GetError());
        } else {
            // Get image dimensions
            m_width = imageSurface->w;
            m_height = imageSurface->h;

            // Set member renderer
            m_renderer = renderer;
        }

        // Free the image surface
        SDL_FreeSurface(imageSurface);
    }

    return m_texture != nullptr;
}

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
bool Expedition::Texture::loadFromRenderedText(std::string text, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer) {
    // Free existing texture
    free();

    // Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == nullptr) {
        printf("ERROR: Unable to render text surface. SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        // Create texture from surface
        m_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (m_texture == nullptr) {
            printf("ERROR: Unable to create texture from rendered text. SDL Error: %s\n", SDL_GetError());
        } else {
            // Get image dimensions
            m_width = textSurface->w;
            m_height = textSurface->h;

            // Set member renderer
            m_renderer = renderer;
        }

        // Free the text surface
        SDL_FreeSurface(textSurface);
    }

    return m_texture != nullptr;
}
#endif

void Expedition::Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    // Set rendering space
    SDL_Rect renderRect = {x, y, m_width, m_height};

    // Set clip rendering dimensions
    if (clip != nullptr) {
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopyEx(m_renderer, m_texture, clip, &renderRect, angle, center, flip);
}

void Expedition::Texture::free() {
    // Free texture if it exists
    if (m_texture != nullptr) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        m_renderer = nullptr;
        m_width = 0;
        m_height = 0;
    }
}

void Expedition::Texture::setColor(uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetTextureColorMod(m_texture, r, g, b);
}

void Expedition::Texture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(m_texture, blending);
}

void Expedition::Texture::setAlpha(uint8_t a) {
    SDL_SetTextureAlphaMod(m_texture, a);
}

int Expedition::Texture::getWidth() {
    return m_width;
}

int Expedition::Texture::getHeight() {
    return m_height;
}
