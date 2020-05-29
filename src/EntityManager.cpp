/**
 * Entity.cpp
 * 
 * Holds all the entities in the game and iterates their properties every frame.
 * 
 */

#pragma once

#include "./EntityManager.h"
#include "./Collision.h"
#include "./Components/ColliderComponent.h"
#include <iostream>

// Logs every entity that has a ColliderComponent
void EntityManager::LogCollisionEntities() {
    for (auto& entity : this->entities) {
        if (entity->HasComponent<ColliderComponent>()) {
            this->collisionEntities.emplace_back(entity);
        }
    }
}

// Destroy all entities
void EntityManager::ClearData() {
    for (auto& entity: this->entities) {
        entity->Destroy();
    }
}

// Returns true if no entities attached to scene
bool EntityManager::HasNoEntities() {
    return entities.size() == 0;
}

// Update all entities
void EntityManager::Update(float deltaTime) {
    for (auto& entity: this->entities) {
        entity->Update(deltaTime);
    }
}

// Render all entities
// Has to find the layers every frame, inefficient.
// Should sort entities into a vector of layers once and then draw from that.
void EntityManager::Render() {
    // RESTORE THIS LATER
    /*for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
        for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber))) { 
            if (entity->name != "Tilee") {
                //std::cout << "Rendering: " << entity->name << std::endl;
            }
            entity->Render();
        }
    }*/
    
    //std::cout << this->entities.size() << std::endl;
    
    // OLD IMPLEMENTATION for testing purposes
    for (auto& entity : this->entities) {
        entity->Render();
    }
}

// Adds an entity to EntityManager
// Should ideally sort entities here so it doesn't have to be done later
Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
    Entity* entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return this->entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const { // Naive approach.
    std::vector <Entity*> selectedEntities;
    for (auto& entity : entities) {
        if (entity->layer == layer) {
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

// Gets the number of entities
unsigned int EntityManager::GetEntityCount() {
    return this->entities.size();
}

// Prints the name of all entities
void EntityManager::PrintAllEntities() {
    std::cout << "Total Entities: " << GetEntityCount() << std::endl;
    for (auto& entity : this->entities) {
        std::cout << "> " << entity->name << ":" << std::endl;
        entity->PrintAllComponents();
    }
}

// Prints out all collisionEntities
void EntityManager::PrintCollisionEntities() {
    for (auto& entity : this->collisionEntities) {
        std::cout << "CollisionEntities:" << std::endl;
        std::cout << "-- " << entity->name << std::endl;
    }
}

// Checks all collisions
std::vector<CollisionEvent> EntityManager::CheckCollisions() const {
    std::vector<CollisionEvent> collisionEvents;
    for (int i = 0; i < collisionEntities.size() - 1; i++) {
        for (int j = i + 1; j < collisionEntities.size(); j++) {
            // Check if collider at j and collider at i are colliding (using Collision::CheckRectangleCollision, returns true/false)
            ColliderComponent* colliderA = collisionEntities[i]->GetComponent<ColliderComponent>();
            ColliderComponent* colliderB = collisionEntities[j]->GetComponent<ColliderComponent>();
            if (Collision::CheckRectangleCollision(colliderA->collider, colliderB->collider)) {
                // If true, find type of collision
                // If valid collision type, save it and the two colliding entities into collisionEvents
                std::cout << "Colliding" << std::endl;
                std::cout << "--- ColliderA: " << collisionEntities[i]->name << ", " << colliderA->colliderTag << std::endl;
                std::cout << "--- ColliderB: " << collisionEntities[j]->name << ", " << colliderB->colliderTag << std::endl;
                if (colliderA->colliderTag.compare("PLAYER") == 0 && colliderB->colliderTag.compare("ENEMY") == 0) {
                    collisionEvents.emplace_back(CollisionEvent{PLAYER_ENEMY_COLLISION, collisionEntities[i], collisionEntities[j]}); // Add to collisionEvents vector
                }
                else if (colliderA->colliderTag.compare("PLAYER") == 0 && colliderB->colliderTag.compare("PROJECTILE") == 0) {
                    collisionEvents.emplace_back(CollisionEvent{PLAYER_PROJECTILE_COLLISION, collisionEntities[i], collisionEntities[j]}); // Add to collisionEvents vector
                }
                else if (colliderA->colliderTag.compare("ENEMY") == 0 && colliderB->colliderTag.compare("FRIENDLY_PROJECTILE") == 0) {
                    collisionEvents.emplace_back(CollisionEvent{ENEMY_PROJECTILE_COLLISION, collisionEntities[i], collisionEntities[j]}); // Add to collisionEvents vector
                }
                else if (colliderA->colliderTag.compare("PLAYER") == 0 && colliderB->colliderTag.compare("LEVEL_COMPLETE") == 0) {
                    collisionEvents.emplace_back(CollisionEvent{PLAYER_LEVEL_COMPLETE_COLLISION, collisionEntities[i], collisionEntities[j]}); // Add to collisionEvents vector
                }
            }
        }
    }
    return collisionEvents;
}