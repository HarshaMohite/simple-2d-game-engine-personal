#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
        void Initialize(int width, int height);
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();
};