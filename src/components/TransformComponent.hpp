#pragma once

#include "../Constants.hpp"
#include "../EntityManager.hpp"
#include "../Game.hpp"
#include <SDL2/SDL.h>
#include <iostream>

class TransformComponent : public Component
{
public:
    glm::vec2 position;
    glm::vec2 velocity;
    int width;
    int height;
    int scale;

    TransformComponent(int t_posX, int t_posY, int t_velX, int t_velY, int t_w, int t_h,
                       int t_s)
    {
        position = glm::vec2(t_posX, t_posY);
        velocity = glm::vec2(t_velX, t_velY);
        width = t_w;
        height = t_h;
        scale = t_s;
    }

    void initialize() override {}

    void update(float t_deltaTime) override
    {
        auto projectedXValue = (position.x + (velocity.x * t_deltaTime));
        // std::cout << projectedXValue << "\n";

        if (projectedXValue <= WINDOW_WIDTH - width && projectedXValue > 0)
        {
            position.x += velocity.x * t_deltaTime;
        }

        auto projectedYValue = (position.y + (velocity.y * t_deltaTime));
        // std::cout << projectedYValue << "\n";

        if (projectedYValue <= WINDOW_HEIGHT - height && projectedYValue > 0)
        {
            position.y += velocity.y * t_deltaTime;
        }
    }
};
