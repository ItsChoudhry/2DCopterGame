#pragma once

#include "../../lib/glm/glm.hpp"
#include "../Component.hpp"
#include "../EntityManager.hpp"
#include "TransformComponent.hpp"

class ProjectileEmitterComponent : public Component
{
private:
    TransformComponent *m_transform;
    glm::vec2 m_origin;
    int m_speed;
    int m_range;
    float m_angleRad;
    bool m_loop;

public:
    ProjectileEmitterComponent(int t_speed, int t_angleDeg, int t_range, bool t_loop)
    {
        m_speed = t_speed;
        m_range = t_range;
        m_angleRad = glm::radians(static_cast<float>(t_angleDeg));
        m_loop = t_loop;
    }

    void initialize() override
    {
        m_transform = owner->getComponent<TransformComponent>();
        m_origin = glm::vec2(m_transform->position.x, m_transform->position.y);
        m_transform->velocity =
            glm::vec2(glm::cos(m_angleRad) * m_speed, glm::sin(m_angleRad) * m_speed);
    }

    void update(float t_deltaTime) override
    {
        if (glm::distance(m_transform->position, m_origin) > m_range)
        {
            if (m_loop)
            {
                m_transform->position.x = m_origin.x;
                m_transform->position.y = m_origin.y;
            }
            else
            {
                owner->destory();
            }
        }
    }
};
