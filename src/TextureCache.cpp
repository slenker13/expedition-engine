#include "TextureCache.hpp"

Expedition::TextureCache::TextureCache() {
    m_renderer = nullptr;
    m_textureMap.clear();
}

Expedition::TextureCache::TextureCache(SDL_Renderer* renderer) : m_renderer(renderer) {
    m_textureMap.clear();
}

Expedition::TextureCache::~TextureCache() {
    m_renderer = nullptr;

    // Free textures in map
    for (auto it = m_textureMap.begin(); it != m_textureMap.end(); it++) {
        delete it->second;
    }
    m_textureMap.clear();
}

void Expedition::TextureCache::setRenderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

Expedition::Texture* Expedition::TextureCache::getTexture(std::string texturePath) {
    // Check if texture exists in the map
    auto it =  m_textureMap.find(texturePath);

    // If texture is not in the map
    if (it == m_textureMap.end()) {
        // Check if renderer is set
        if (m_renderer == nullptr) {
            printf("ERROR: Renderer is null. Set renderer before getting textures.\n");
            return nullptr;
        } else {
            // Load the new texture
            Texture* newTexture = new Texture;
            if (!newTexture->loadFromFile(texturePath, m_renderer)) {
                printf("ERROR: Failed to load texture from %s.\n", texturePath.c_str());
                return nullptr;
            } else {
                // Insert the new texture into the map and return a pointer to the texture
                auto newIt = m_textureMap.emplace(texturePath, newTexture).first;
                printf("Loaded new texture from %s\n", newIt->first.c_str());
                return newIt->second;
            }
        }
    }

    // If texture exists in the map, return a pointer to it
    return it->second;
}
