#pragma once

#include "Component.hpp"
#include "EntityManager.hpp"
#include <map>
#include <string>
#include <vector>

class EntityManager;
class Component;

class Entity
{
private:
    EntityManager &m_manager;
    bool m_active;
    std::vector<Component *> m_components;
    std::map<const std::type_info *, Component *> m_componentTypeMap;

public:
    std::string name;
    Entity(EntityManager &t_manager);
    Entity(EntityManager &t_manager, std::string t_name);
    void update(float t_deltaTime);
    void render();
    void destory();
    bool isActive() const;

    template <typename T, typename... TAgrs>
    T &addComponent(TAgrs &&... args)
    {
        T *newComponent(new T(std::forward<TAgrs>(args)...));
        newComponent->owner = this;
        m_components.emplace_back(newComponent);
        m_componentTypeMap[&typeid(*newComponent)] = newComponent;
        newComponent->initialize();
        return *newComponent;
    }

    template <typename T>
    T *getComponent()
    {
        return static_cast<T *>(m_componentTypeMap[&typeid(T)]);
    }
};
