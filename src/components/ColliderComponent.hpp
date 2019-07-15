#pragma once

#include "../Component.hpp"
#include "../EntityManager.hpp"
#include "../Game.hpp"
#include "TransformComponent.hpp"
#include <SDL2/SDL.h>
#include <string>

class ColliderComponent : public Component
{
private:
    /* data */
public:
    std::string colliderTag;
    SDL_Rect colliderRect;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
    TransformComponent *transform;

    ColliderComponent(std::string t_colliderTag, int t_x, int t_y, int t_width,
                      int t_height)
    {
        colliderTag = t_colliderTag;
        colliderRect = {t_x, t_y, t_width, t_height};
    }

    void initialize() override
    {
        if (owner->hasComponent<TransformComponent>())
        {
            transform = owner->getComponent<TransformComponent>();
            sourceRect = {0, 0, transform->width, transform->height};
            destinationRect = {colliderRect.x, colliderRect.y, colliderRect.w,
                               colliderRect.h};
        }
    }

    void update(float t_deltaTime) override
    {
        colliderRect.x = static_cast<int>(transform->position.x);
        colliderRect.y = static_cast<int>(transform->position.y);
        colliderRect.w = transform->width * transform->scale;
        colliderRect.h = transform->height * transform->scale;
        destinationRect.x = colliderRect.x - Game::camera.x;
        destinationRect.y = colliderRect.y - Game::camera.y;
    }
};
