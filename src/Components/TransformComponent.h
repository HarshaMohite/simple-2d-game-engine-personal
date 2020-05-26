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
        int width;
        int height;
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
            //position.x = std::clamp(static_cast<int>(position.x), 0, static_cast<int>(WINDOW_WIDTH));
            //position.y = std::clamp(static_cast<int>(position.y), 0, static_cast<int>(WINDOW_HEIGHT));
            
            // Check if outside window bounds, clamp
            if (position.x < 0.f) {
                position.x = 0.f;
            } else if (position.x + static_cast<float>(this->width) > static_cast<float>(WINDOW_WIDTH)) {
                position.x = static_cast<float>(WINDOW_WIDTH) - static_cast<float>(this->width);
            }
            if (position.y < 0.f) {
                position.y = 0.f;
            } else if (position.y + static_cast<float>(this->height) > static_cast<float>(WINDOW_HEIGHT)) {
                position.y =  static_cast<float>(WINDOW_HEIGHT) - static_cast<float>(this->height);
            }
        }

        void Render() override {
            /*SDL_Rect transformRectangle = {
                (int) this->position.x,
                (int) this->position.y,
                this->width,
                this->height
            };
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(Game::renderer, &transformRectangle);*/
        }
};