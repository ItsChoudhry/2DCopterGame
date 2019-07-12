#include "EntityManager.hpp"
#include <iostream>

void EntityManager::clearData()
{
    for (auto &&entity : m_entities)
    {
        entity->destory();
    }
}

bool EntityManager::hasNoEntities() { return m_entities.size() == 0; }

void EntityManager::update(float t_deltaTime)
{
    for (auto &&entity : m_entities)
    {
        entity->update(t_deltaTime);
    }
}

void EntityManager::render()
{
    for (int layerNum = 0; layerNum < NUM_LAYERS; layerNum++)
    {
        for (auto &&entity : getEntitiesByLayer(static_cast<LayerType>(layerNum)))
        {
            entity->render();
        }
    }
}

Entity &EntityManager::addEntity(std::string t_entityName, LayerType t_layer)
{
    Entity *entity = new Entity(*this, t_entityName, t_layer);
    m_entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity *> EntityManager::getEntities() const { return m_entities; }

unsigned int EntityManager::getEntityCount() { return m_entities.size(); }

void EntityManager::listAllEntities() const
{
    unsigned int i = 0;
    for (auto &&entity : m_entities)
    {
        std::cout << "Entity[" << i << "] " << entity->name << "\n";
        entity->listAllComponents();
        i++;
    }
}

std::vector<Entity *> EntityManager::getEntitiesByLayer(LayerType t_layer) const
{
    std::vector<Entity *> selectedEntities;
    for (auto &&entity : m_entities)
    {
        if (entity->layer == t_layer)
        {
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}
