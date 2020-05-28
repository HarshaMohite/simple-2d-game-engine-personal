#pragma once

#include <SDL2/SDL.h>

class Collision {
    public:
        static bool CheckRectangleCollision(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB); // AABB - Axis-Aligned Bounding-Box
};