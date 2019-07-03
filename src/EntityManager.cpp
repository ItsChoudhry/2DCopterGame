#include "EntityManager.hpp"

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
    for (auto &&entity : m_entities)
    {
        entity->render();
    }
}

Entity &EntityManager::addEntity(std::string t_entityName)
{
    Entity *entity = new Entity(*this, t_entityName);
    m_entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity *> EntityManager::getEntities() const { return m_entities; }

unsigned int EntityManager::getEntityCount() { return m_entities.size(); }
