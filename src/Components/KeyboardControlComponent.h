#pragma once

#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"


class KeyboardControlComponent : public Component {
    private:
        bool upKeyDown = false;
        bool rightKeyDown = false;
        bool downKeyDown = false;
        bool leftKeyDown = false;

    public:
        std::string upKey;
        std::string downKey;
        std::string rightKey;
        std::string leftKey;
        std::string shootKey;
        TransformComponent* transform;
        SpriteComponent* sprite;
        std::string keyboardControlComponentName = "Keyboard_Control_Component";
        int movementSpeed = 150;

        KeyboardControlComponent() {
            this->componentName = keyboardControlComponentName;
        }

        // Get keys and convert member variables to SDL key codes
        KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey) {
            this->componentName = keyboardControlComponentName;
            this->upKey = GetSDLKeyStringCode(upKey);
            this->rightKey = GetSDLKeyStringCode(rightKey);
            this->downKey = GetSDLKeyStringCode(downKey);
            this->leftKey = GetSDLKeyStringCode(leftKey);
            this->shootKey = GetSDLKeyStringCode(shootKey);
        }

        // Gets SDL key code
        std::string GetSDLKeyStringCode(std::string key) {
            // Taken from SDL documentation
            if (key.compare("up") == 0) return "1073741906";
            if (key.compare("down") == 0) return "1073741905";
            if (key.compare("left") == 0) return "1073741904";
            if (key.compare("right") == 0) return "1073741903";
            if (key.compare("space") == 0) return "32";
            return std::to_string(static_cast<int>(key[0]));
        }

        void Initialize() override {
            // TODO: Check if these components exist
            transform = owner->GetComponent<TransformComponent>();
            sprite = owner->GetComponent<SpriteComponent>();
        }

        void Update(float deltaTime) override {
            if (Game::event.type == SDL_KEYDOWN) {
                std::string keyCode = std::to_string(Game::event.key.keysym.sym);
                if (keyCode.compare(upKey) == 0) {
                    upKeyDown = true;
                    transform->velocity.y = -movementSpeed;
                    transform->velocity.x = 0;
                    sprite->Play("UpAnimation");
                }
                if (keyCode.compare(rightKey) == 0) {
                    rightKeyDown = true;
                    transform->velocity.y = 0;
                    transform->velocity.x = movementSpeed;
                    sprite->Play("RightAnimation");
                }
                if (keyCode.compare(downKey) == 0) {
                    downKeyDown = true;
                    transform->velocity.y = movementSpeed;
                    transform->velocity.x = 0;
                    sprite->Play("DownAnimation");
                }
                if (keyCode.compare(leftKey) == 0) {
                    leftKeyDown = true;
                    transform->velocity.y = 0;
                    transform->velocity.x = -movementSpeed;
                    sprite->Play("LeftAnimation");
                }
                if (keyCode.compare(shootKey) == 0) {
                    // TODO:
                    // Shoot projectiles when 'shoot' key is pressed
                }
            }

            if (Game::event.type == SDL_KEYUP) {
                std::string keyCode = std::to_string(Game::event.key.keysym.sym);
                if (keyCode.compare(upKey) == 0) {
                    upKeyDown = false;
                    transform->velocity.y = 0;
                }
                if (keyCode.compare(rightKey) == 0) {
                    rightKeyDown = false;
                    transform->velocity.x = 0;
                }
                if (keyCode.compare(downKey) == 0) {
                    downKeyDown = false;
                    transform->velocity.y = 0;
                }
                if (keyCode.compare(leftKey) == 0) {
                    leftKeyDown = false;
                    transform->velocity.x = 0;
                }
                if (rightKeyDown) {
                    transform->velocity.x = movementSpeed;
                    sprite->Play("RightAnimation");
                }
                if (leftKeyDown) {
                    transform->velocity.x = -movementSpeed;
                    sprite->Play("LeftAnimation");
                }
                if (upKeyDown) {
                    transform->velocity.y = -movementSpeed;
                    sprite->Play("UpAnimation");
                }
                if (downKeyDown) {
                    transform->velocity.y = movementSpeed;
                    sprite->Play("DownAnimation");
                }
            }


        }


};