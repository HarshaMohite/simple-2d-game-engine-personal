#include "Entity.h"
#include <iostream>

Entity::Entity(EntityManager& manager): manager(manager) {
    this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name, LayerType layer): manager(manager), name(name), layer(layer) {
    this->isActive = true;
}

void Entity::Update(float deltaTime) {
    for (auto& component: components) {
        component->Update(deltaTime);
    }
}

void Entity::Render() {
    for (auto& component: components) {
        component->Render();
    }
}

void Entity::Destroy() {
    this->isActive = true;

}

bool Entity::IsActive() const {
    return this->isActive;
}

// Prints the name of all components on an indented line
void Entity::PrintAllComponents() {
    for (auto& component : this->components) {
        std::cout << "\t-- " << component->GetComponentName() << std::endl;
    }
}