#pragma once

#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>
#include "../Game.h"

class TransformComponent: public Component {
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
        }

        void Render() override {
            SDL_Rect transformRectangle = {
                (int) this->position.x,
                (int) this->position.y,
                this->width,
                this->height
            };
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(Game::renderer, &transformRectangle);
        }
};