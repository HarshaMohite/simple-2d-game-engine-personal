#pragma once

#include <vector>
#include <string>
#include "Component.h"

// REMOVE LATER
//class Component;
//class EntityManager;

class EntityManager;

#include "EntityManager.h"

class Entity {
    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component*> components;

    public:
        std::string name;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;
        void PrintAllComponents();

        // Add component to this entity
        template <typename T, typename... TArgs> // Define template
        T& AddComponent(TArgs&&... args) { // Take in arguments and return newly created object
            T* newComponent(new T(std::forward<TArgs>(args)...)); //Create new component
            newComponent->owner = this; // Set component's owner to this entity
            components.emplace_back(newComponent); // Add this component to the end of the components vector list
            newComponent->Initialize(); // Call initialize on that new component
            return *newComponent; // Return the new component
        }
};
