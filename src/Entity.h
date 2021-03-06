#pragma once

#include <vector>
#include <string>
#include <map>
#include "./Component.h"
#include "./Constants.h"

class EntityManager;

#include "EntityManager.h"

class Entity {
    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component*> components;
        std::map<const std::type_info*, Component*> componentTypeMap;

    public:
        std::string name;
        LayerType layer;
        Entity(EntityManager& manager);
        Entity(EntityManager& manager, std::string name, LayerType layer);
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;
        void PrintAllComponents();

        // Returns true if component is found
        template <typename T>
        bool HasComponent() const {
            return this->componentTypeMap.count(&typeid(T)); // Much more elegant solution
            /*for (auto& component : this->componentTypeMap) {
                if (component.first == &typeid(T)) {
                    return true;
                }
            }
            return false;*/
        }

        // Add component to this entity
        template <typename T, typename... TArgs> // Define template
        T& AddComponent(TArgs&&... args) { // Take in arguments and return newly created object
            T* newComponent(new T(std::forward<TArgs>(args)...)); //Create new component
            newComponent->owner = this; // Set component's owner to this entity
            components.emplace_back(newComponent); // Add this component to the end of the components vector list
            componentTypeMap[&typeid(*newComponent)] = newComponent; // Add this component to the componentTypeMap
            newComponent->Initialize(); // Call initialize on that new component
            return *newComponent; // Return the new component
        }

        template <typename T>
        T* GetComponent() {
            return static_cast<T*>(componentTypeMap[&typeid(T)]);
        }
};
