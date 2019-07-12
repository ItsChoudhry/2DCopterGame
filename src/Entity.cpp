#include "Entity.hpp"
#include <iostream>

Entity::Entity(EntityManager &t_manager) : m_manager(t_manager)
{
    this->m_active = true;
}

Entity::Entity(EntityManager &t_manager, std::string t_name, LayerType t_layer)
    : m_manager(t_manager), name(t_name), layer(t_layer)
{
    this->m_active = true;
}

void Entity::update(float t_deltaTime)
{
    for (auto &&component : m_components)
    {
        component->update(t_deltaTime);
    }
}

void Entity::render()
{
    for (auto &&component : m_components)
    {
        component->render();
    }
}

void Entity::destory() { this->m_active = false; }

bool Entity::isActive() const { return this->m_active; }

void Entity::listAllComponents() const
{
    for (auto &&mapElement : m_componentTypeMap)
    {
        std::cout << "    Component<" << mapElement.first->name() << "> \n";
    }
}
