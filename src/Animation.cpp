#include "./Animation.h"

/**
 * Animation.cpp
 * 
 * Implements methods for handling animated sprites.
 *
 */

Animation::Animation() {
    this->index = 0;
    this->numFrames = 0;
    this->animationSpeed = 0;
};

Animation::Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed) {
    this->index = index;
    this->numFrames = numFrames;
    this->animationSpeed = animationSpeed;
}