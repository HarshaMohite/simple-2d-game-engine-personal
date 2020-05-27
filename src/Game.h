#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./Entity.h"
#include "./Component.h"
#include "./EntityManager.h"
#include "./Map.h"

class AssetManager;

class Game {
    private:
        bool isRunning;
        SDL_Window *window;
    
    public:
        Game();
        ~Game();
        bool IsRunning() const;
        int ticksLastFrame = 0;
        static SDL_Renderer *renderer;
        static AssetManager* assetManager;
        static SDL_Event event;
        static SDL_Rect camera;
        static Map* map;
        void LoadLevel(int levelNumber);
        void Initialize(int width, int height);
        void ProcessInput();
        void Update();
        void Render();
        void HandleCameraMovement();
        void Destroy();
};