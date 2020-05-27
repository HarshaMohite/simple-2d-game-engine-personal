#pragma once

#include <SDL2/SDL.h>
//#include "../TextureManager.h"
#include "../AssetManager.h"
#include "./TransformComponent.h"
#include "../Animation.h"

/**
 * SpriteComponent.h
 * 
 * Displays a texture on the screen for the entity.
 * Initiates the handling of animations, if sprite is animated.
 * 
 */

class SpriteComponent : public Component {
    private:
        std::string spriteComponentName = "Sprite_Component";
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceRectangle; // Rectangle for drawing from source (where on the texture)
        SDL_Rect destinationRectangle; // Rectangle for drawing to render target (where to in screen space)
        bool isAnimated;
        int numFrames;
        int animationSpeed;
        bool isFixed; // true if sprite has a fixed position, doesn't change depending on camera movement
        std::map<std::string, Animation> animations;
        std::string currentAnimationName;
        unsigned int animationIndex = 0;
    
    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent(std::string assetTextureId) {
            isAnimated = false;
            isFixed = false;
            SetTexture(assetTextureId);
            this->componentName = spriteComponentName;
        }

        // Constructor for animated sprites
        SpriteComponent(std::string assetTextureId, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
            this->isAnimated = true;
            this->numFrames = numFrames;
            this->animationSpeed = animationSpeed;
            this->isFixed = isFixed;
            this->componentName = spriteComponentName;

            if (hasDirections) { // Assumption is 4 directions
                
                // Creates four animations
                Animation downAnimation = Animation(0, numFrames, animationSpeed);
                Animation rightAnimation = Animation(1, numFrames, animationSpeed);
                Animation leftAnimation = Animation(2, numFrames, animationSpeed);
                Animation upAnimation = Animation(3, numFrames, animationSpeed);

                // Adds them to animations map
                animations.emplace("DownAnimation", downAnimation);
                animations.emplace("RightAnimation", rightAnimation);
                animations.emplace("LeftAnimation", leftAnimation);
                animations.emplace("UpAnimation", upAnimation);

                this->animationIndex = 0;
                this->currentAnimationName = "DownAnimation";
            } else {
                Animation singleAnimation = Animation(0, numFrames, animationSpeed);
                animations.emplace("SingleAnimation", singleAnimation);
                this->animationIndex = 0;
                this->currentAnimationName = "SingleAnimation";
            }

            Play(this->currentAnimationName);

            SetTexture(assetTextureId);

            
        }

        void Play(std::string animationName) {
            numFrames = animations[animationName].numFrames;
            animationIndex = animations[animationName].index;
            animationSpeed = animations[animationName].animationSpeed;
            currentAnimationName = animationName;
        }

        // Sets texture for this sprite component
        void SetTexture(std::string assetTextureId) {
            this->texture = Game::assetManager->GetTexture(assetTextureId);
        }

        void Initialize() override {
            if (!owner->HasComponent<TransformComponent>()) {
                owner->AddComponent<TransformComponent>(0, 0, 0, 0, 32, 32, 1); // Create new TransformComponent if none exists
            }
            transform = owner->GetComponent<TransformComponent>(); // Gets existing TransformComponent from owning entity

            this->sourceRectangle.x = 0;
            this->sourceRectangle.y = 0;
            // Sets source rectangle width/height to transform width/height
            this->sourceRectangle.w = transform->width;
            this->sourceRectangle.h = transform->height;
        }

        void Update(float deltaTime) override {
            if (isAnimated) {
                sourceRectangle.x = (sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames)); // Modulus loops over animations, never exceeding the last frame
            }
            sourceRectangle.y = animationIndex * transform->height;

            this->destinationRectangle.x = static_cast<int>(transform->position.x);
            this->destinationRectangle.y = static_cast<int>(transform->position.y);
            this->destinationRectangle.w = transform->width * transform->scale;
            this->destinationRectangle.h = transform->height * transform->scale;
        }

        void Render() override {
            TextureManager::Draw(texture, sourceRectangle, destinationRectangle, this->spriteFlip);
        }
};