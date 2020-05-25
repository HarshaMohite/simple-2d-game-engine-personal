#pragma once

#include <SDL2/SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "./TransformComponent.h"

/**
 * SpriteComponent.h
 * 
 * Displays a texture on the screen for the entity.
 * 
 */

class SpriteComponent : public Component {
    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
    
    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent(const char* filePath) {
            SetTexture(filePath);
            this->componentName = "Sprite_Component";
        }

        // Sets texture for this sprite component
        void SetTexture(std::string assetTextureId) {
            this->texture = Game::assetManager->GetTexture(assetTextureId);
        }

        void Initialize() override {
            transform = owner->GetComponent<TransformComponent>();
            this->sourceRectangle.x = 0;
            this->sourceRectangle.y = 0;
            this->sourceRectangle.w = transform->width;
            this->sourceRectangle.h = transform->height;
        }

        void Update(float deltaTime) override {
            this->destinationRectangle.x = (int) transform->position.x;
            this->destinationRectangle.y = (int) transform->position.y;
            this->destinationRectangle.w = transform->width * transform->scale;
            this->destinationRectangle.h = transform->height * transform->scale;
        }

        void Render() override {
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, this->spriteFlip);
        }
};