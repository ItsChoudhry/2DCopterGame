#include "Entity.hpp"

Entity::Entity(EntityManager &t_manager) : m_manager(t_manager)
{
    this->m_active = true;
}

Entity::Entity(EntityManager &t_manager, std::string t_name)
    : m_manager(t_manager), name(t_name)
{
    this->m_active = true;
}

void Entity::update(float t_deltaTime)
{
    for (auto &&Component : m_components)
    {
        Component->update(t_deltaTime);
    }
}

void Entity::destory() { this->m_active = false; }

bool Entity::isActive() const { return this->m_active; }
