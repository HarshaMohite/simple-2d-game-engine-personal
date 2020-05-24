#include "./AssetManager.h"

AssetManager::AssetManager(EntityManager* manager): manager(manager) {}

// Clears everything from asset map
void AssetManager::ClearData() {
    textures.clear();
}

// Adds texture to asset map
void AssetManager::AddTexture(std::string textureId, const char* filePath) {
    textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

// Returns texture from asset map
SDL_Texture* AssetManager::GetTexture(std::string textureId) {
    return textures[textureId];
}