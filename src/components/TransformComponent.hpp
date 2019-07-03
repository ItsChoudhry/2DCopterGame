#pragma once

#include "../EntityManager.hpp"
#include "../Game.hpp"
#include <SDL2/SDL.h>

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
        position.x += velocity.x * t_deltaTime;
        position.y += velocity.y * t_deltaTime;
    }

    void render() override
    {
        SDL_Rect transformRectangle = {static_cast<int>(std::round(position.x)),
                                       static_cast<int>(std::round(position.y)), width,
                                       height};
    }

    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(Game::renderer, &transformRectangle);
}
