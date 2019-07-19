#include "EntityManager.hpp"
#include "Collision.hpp"
#include "components/ColliderComponent.hpp"
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
    destoryInactiveEntities();
}

void EntityManager::destoryInactiveEntities()
{
    for (int i = 0; i < m_entities.size(); i++)
    {
        if (!m_entities[i]->isActive())
        {
            m_entities.erase(m_entities.begin() + i);
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

Entity *EntityManager::getEntityByName(std::string t_entityName) const
{
    for (auto *entity : m_entities)
    {
        if (entity->name.compare(t_entityName) == 0)
        {
            return entity;
        }
    }
    return nullptr;
}

CollisionType EntityManager::checkCollisions() const
{
    for (auto &&thisEntity : m_entities)
    {
        if (thisEntity->hasComponent<ColliderComponent>())
        {
            ColliderComponent *thisCollider =
                thisEntity->getComponent<ColliderComponent>();
            for (auto &&thatEntity : m_entities)
            {
                if (thisEntity->name.compare(thatEntity->name) != 0 &&
                    thatEntity->hasComponent<ColliderComponent>())
                {
                    ColliderComponent *thatCollider =
                        thatEntity->getComponent<ColliderComponent>();
                    if (Collision::checkRectCollision(thisCollider->colliderRect,
                                                      thatCollider->colliderRect))
                    {
                        if (thisCollider->colliderTag.compare("PLAYER") == 0 &&
                            thatCollider->colliderTag.compare("ENEMY") == 0)
                        {
                            return PLAYER_ENEMY_COLLISION;
                        }
                        if (thisCollider->colliderTag.compare("PLAYER") == 0 &&
                            thatCollider->colliderTag.compare("PROJECTILE") == 0)
                        {
                            return PLAYER_PROJECTILE_COLLISION;
                        }
                        if (thisCollider->colliderTag.compare("ENEMY") == 0 &&
                            thatCollider->colliderTag.compare("FRIENDLY_PROJECTILE") ==
                                0)
                        {
                            return ENEMY_PROJECTILE_COLLISION;
                        }
                        if (thisCollider->colliderTag.compare("PLAYER") == 0 &&
                            thatCollider->colliderTag.compare("level_complete") == 0)
                        {
                            return PLAYER_LEVEL_COMPLETE_COLLISION;
                        }
                    }
                }
            }
        }
    }
    return NO_COLLISION;
}
