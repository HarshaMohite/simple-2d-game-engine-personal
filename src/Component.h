#pragma once
#include <string>

// REMOVE LATER
class Entity;

class Component {
    public:
        Entity* owner;
        virtual ~Component() {}
        virtual void Initialize() {}
        virtual void Update(float deltaTime) {}
        virtual void Render() {}

        std::string GetComponentName() {
            return this->componentName;
        }

    protected:
        std::string componentName;
};