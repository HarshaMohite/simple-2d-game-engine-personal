#pragma once

#include "Component.h"
#include <vector>
#include "Constants.h"

class Entity;

#include "Entity.h"

class EntityManager {
    private:
        std::vector<Entity*> entities;
    
    public:
        std::vector<Entity*> collisionEntities;
        void LogCollisionEntities();
        void ClearData();
        void Update(float deltaTime);
        void Render();
        bool HasNoEntities();
        Entity& AddEntity(std::string entityName, LayerType layer);
        std::vector<Entity*> GetEntities() const;
        std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
        unsigned int GetEntityCount();
        void PrintAllEntities();
        std::string CheckEntityCollisions(Entity& entity) const;
        std::vector<CollisionEvent> CheckCollisions() const;
        //CollisionType CheckCollisions() const;

};