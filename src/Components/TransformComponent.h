#pragma once

#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>
#include "../Game.h"
#include <algorithm>

/**
 * TransformComponent.h
 * 
 * Adds transform properties to the entity.
 * 
 */

class TransformComponent : public Component {
    public:
        glm::vec2 position;
        glm::vec2 velocity;
        int width; // Width of the entity
        int height; // Height of the entity
        int scale;
        
        TransformComponent(int posX, int posY, int velX, int velY, int width, int height, int scale) {
            this->position = glm::vec2(posX, posY);
            this->velocity = glm::vec2(velX, velY);
            this->width = width;
            this->height = height;
            this->scale = scale;
            this->componentName = "Transform_Component";
        }

        void Initialize() override {

        }

        void Update(float deltaTime) override {
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
            
            // Check if outside window bounds, clamp
            unsigned int scale = Game::map->getScale();
            if (position.x < 0.f) {
                position.x = 0.f;
            } else if (position.x + static_cast<float>(this->width) > static_cast<float>(WINDOW_WIDTH * scale)) {
                position.x = static_cast<float>(WINDOW_WIDTH * scale) - static_cast<float>(this->width);
            }
            if (position.y < 0.f) {
                position.y = 0.f;
            } else if (position.y + static_cast<float>(this->height) > static_cast<float>(WINDOW_HEIGHT * scale)) {
                position.y =  static_cast<float>(WINDOW_HEIGHT * scale) - static_cast<float>(this->height);
            }
        }

        void Render() override {
            
        }
};