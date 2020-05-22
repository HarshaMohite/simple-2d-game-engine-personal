#pragma once

#include "EntityManager.h"

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
void EntityManager::Render() {
    for (auto& entity: this->entities) {
        entity->Render();
    }
}

// Adds an entity to EntityManager
Entity& EntityManager::AddEntity(std::string entityName) {
    Entity* entity = new Entity(*this, entityName);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return this->entities;
}

unsigned int EntityManager::GetEntityCount() {
    return this->entities.size();
}