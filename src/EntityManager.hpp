#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include <string>
#include <vector>

class EntityManager
{
private:
    std::vector<Entity *> m_entities;

public:
    void clearData();
    void update(float t_deltaTime);
    void render();
    bool hasNoEntities();
    Entity &addEntity(std::string t_entityName, LayerType t_layer);
    std::vector<Entity *> getEntities() const;
    std::vector<Entity *> getEntitiesByLayer(LayerType t_layer) const;
    unsigned int getEntityCount();
    void listAllEntities() const;
    CollisionType checkCollisions() const;
    void destoryInactiveEntities();
};
