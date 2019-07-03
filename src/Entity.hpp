#pragma once

#include <string>
#include <vector>

#include "Component.hpp"
#include "EntityManager.hpp"

class EntityManager;
class Component;

class Entity
{
private:
    EntityManager &m_manager;
    bool m_active;
    std::vector<Component *> m_components;

public:
    std::string name;
    Entity(EntityManager &t_manager);
    Entity(EntityManager &t_manager, std::string t_name);
    void update(float t_deltaTime);
    void render();
    void destory();
    bool isActive() const;
};
