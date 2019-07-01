#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../lib/glm/glm.hpp"

class Game
{
public:
    bool isRunning() const;
    void initialize(int t_width, int t_height);
    void processInput();
    void update();
    void render();
    void destory();
    int ticksLastFrame;

    glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
    glm::vec2 projectileVel = glm::vec2(20.0f, 20.0f);

private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    bool m_running = false;
};
