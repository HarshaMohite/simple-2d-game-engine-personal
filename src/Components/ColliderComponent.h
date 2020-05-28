#pragma once

#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "./TransformComponent.h"
#include "../AssetManager.h"

class ColliderComponent : public Component {
    public:
        std::string colliderTag;
        SDL_Rect collider;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        TransformComponent* transform;

        ColliderComponent(std::string colliderTag, int x, int y, int width, int height) {
            this->componentName = "Collider_Component";
            this->colliderTag = colliderTag;
            this->collider = {x, y, width, height};
        }

        void Initialize() override {
            if (owner->HasComponent<TransformComponent>()) { // Protection clause
                this->transform = owner->GetComponent<TransformComponent>();
                sourceRectangle = {0, 0, transform->width, transform->height};
                destinationRectangle = {collider.x, collider.y, collider.w, collider.h}; // Initial destination
            }
        }

        void Update(float deltaTime) override {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
            destinationRectangle.x = collider.x - Game::camera.x; // Respond to camera movement
            destinationRectangle.y = collider.y - Game::camera.y;
        }

        void Render() override {
            //TextureManager::Draw(Game::assetManager->GetTexture("collision-texture"), sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
        }
};