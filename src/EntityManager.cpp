/**
 * Entity.cpp
 * 
 * Holds all the entities in the game and iterates their properties every frame.
 * 
 */

#pragma once

#include "EntityManager.h"
#include <iostream>

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
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
        for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber))) { 
            entity->Render();
        }
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