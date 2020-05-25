/**
 * AssetManager.cpp
 * 
 * Stores all the assets in the game, to be called later.
 * 
 * Stores textures, which need to be in an SDL_Texture object,
 * instanced by the TextureManager.
 * 
 */

#include "./AssetManager.h"

AssetManager::AssetManager(EntityManager* manager): manager(manager) {}

// Clears everything from asset map
void AssetManager::ClearData() {
    textures.clear();
}

// Adds texture to asset map
void AssetManager::AddTexture(std::string textureId, const char* filePath) {
    // Gets SDL texture from TextureManager, which implements loading in the texture
    textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

// Returns texture from asset map
SDL_Texture* AssetManager::GetTexture(std::string textureId) {
    return textures[textureId];
}