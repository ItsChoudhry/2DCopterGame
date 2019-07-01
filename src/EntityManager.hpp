#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include <vector>

class EntityManager
{
private:
    std::vector<Entity *> m_entities;

public:
    void update(float t_deltaTime);
    void render();
    void hasNoEntities();
    Entity &addEntity(std::string t_entityName);
    std::vector<Entity *> getEntities() const;
    unsigned int getEntityCount();
};
