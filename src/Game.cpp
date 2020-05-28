/**
 * Game.cpp
 * 
 * Manages the game loop.
 * 
 */

#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./AssetManager.h"
#include "./Map.h"
#include "../lib/glm/glm.hpp"
#include "./Components/SpriteComponent.h"
#include "./Components/TransformComponent.h"
#include "./Components/TestComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Components/ColliderComponent.h"


EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* Game::map;
bool Game::isDebugging; // Why does this have to be called here for static public member variable?

Game::Game() {
    this->isRunning = false;
    this->isDebugging = false; // It is then initialized here, in the constructor... strange.
}

Game::~Game() {

}

bool Game::IsRunning() const {
    return this->isRunning;
}

// Start up SDL and configure settings.
void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { // Initializes SDL
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
    }

    LoadLevel(0);

    LogCollisionEntities();

    //manager.PrintAllEntities();

    isRunning = true;
    return;
}

// Calls LogCollisionEntities() in EntityManager
void Game::LogCollisionEntities() {
    manager.LogCollisionEntities();
}

Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));

// Loads in all the entities for a level
void Game::LoadLevel(int levelNumber) {
    //assetManager->AddTexture("collision-texture", std::string("./assets/images/collision-texture.png").c_str());
    assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("collision-image", std::string("./assets/images/collision-texture.png").c_str());
    assetManager->AddTexture("new-texture", std::string("./assets/images/obstacles.png").c_str()); // Need to add this for some reason, else jungle-tiletexture doesn't load in properly. NO clue why.
    assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
    assetManager->AddTexture("heliport-image", std::string("./assets/images/heliport.png").c_str());
    //assetManager->PrintMap();

    map = new Map("jungle-tiletexture", 2, 32);
    map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

    //chopperEntity.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    player.AddComponent<TransformComponent>(0, 0, 0, 0, 32, 32, 1);
    player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    player.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
    player.AddComponent<ColliderComponent>("PLAYER", 240, 106, 32, 32);
    //player.AddComponent<SpriteComponent>("collision-texture");

    Entity& tankEntity(manager.AddEntity("tank", ENEMY_LAYER)); // Creates reference to an Entity object called "tankEntity", then sets it to the return of manager.AddEntity("tank")
    tankEntity.AddComponent<TransformComponent>(100, 100, 20, 20, 32, 32, 1);
    tankEntity.AddComponent<SpriteComponent>("tank-image");
    tankEntity.AddComponent<ColliderComponent>("ENEMY", 100, 100, 32, 32);
    //tankEntity.AddComponent<SpriteComponent>("collision-texture");

    Entity& heliport(manager.AddEntity("heliport", OBSTACLE_LAYER));
    heliport.AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
    heliport.AddComponent<SpriteComponent>("heliport-image");
    heliport.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

    Entity& radarEntity(manager.AddEntity("radar", UI_LAYER));
    radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);
}

// Get input from user and do something here
void Game::ProcessInput() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            if (event.key.keysym.sym == SDLK_1) {
                isDebugging = true;
            }
            if (event.key.keysym.sym == SDLK_2) {
                isDebugging = false;
            }
            break;
        default:
            break;
    }
}

// Main update function, called from Main.cpp.
// Propagates to all entities and their components.
// Handles delay using SDL library. Framerate limited to 60.
void Game::Update() {
    // Sleep until next frame ready
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    // Delta time is the difference in ticks from last frame converted to seconds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);

    HandleCameraMovement();
    CheckCollisions();
}

// Call Render for every entity and component
void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255); // Grey
    SDL_RenderClear(renderer); // Clears back buffer

    if (manager.HasNoEntities()) {
        return;
    }

    manager.Render();

    SDL_RenderPresent(renderer);
}

// Translate the camera according to the player position
void Game::HandleCameraMovement() {
    TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();
    
    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

    // Clamping camera values
    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > (WINDOW_WIDTH * map->getScale()) - camera.w ? (WINDOW_WIDTH * map->getScale()) - camera.w : camera.x;
    camera.y = camera.y > (WINDOW_HEIGHT * map->getScale()) - camera.h ? (WINDOW_HEIGHT * map->getScale()) - camera.h : camera.y;
}

// Check all collisions, and go off to handle behavior based on certain collision types
void Game::CheckCollisions() {
    //CollisionType collisionType = manager.CheckCollisions();
    std::vector<CollisionEvent> collisions = manager.CheckCollisions(); // Get a record of all collisions
    for (int i = 0; i < collisions.size(); i++) {
        switch (collisions[i].collisionType) {
            case PLAYER_ENEMY_COLLISION:
                ProcessGameOver();
                break;
            case PLAYER_LEVEL_COMPLETE_COLLISION:
                ProcessNextLevel(1);
                break;
        }
    }
    
    // OLD
    /*for (CollisionType currentCollision : collisions) { // Do a check for every collision recorded
        switch (currentCollision) {
            case PLAYER_ENEMY_COLLISION:
                ProcessGameOver();
                break;
            case PLAYER_LEVEL_COMPLETE_COLLISION:
                ProcessNextLevel(1);
                break;
        }
    }*/
    
    // OLD
    /*std::string collisionTagType = manager.CheckEntityCollisions(player);
    if (collisionTagType.compare("enemy") == 0) { // Hardcoded
        // TODO: do something when collision is identified with an enemy
        isRunning = false;
    }*/
}

// Do this to process the next level
void Game::ProcessNextLevel(int levelNumber) {
    std::cout << "Next Level" << std::endl;
    isRunning = false; // Currently closes game, but later should load next level
}

// Do this when the game is over
void Game::ProcessGameOver() {
    std::cout << "Game Over" << std::endl;
    isRunning = false;
}

// Ends processes gracefully
void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}