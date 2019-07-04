#pragma once

#include "../lib/glm/glm.hpp"
#include "Component.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game
{
public:
    Game();
    ~Game();
    bool isRunning() const;
    void initialize(int t_width, int t_height);
    void processInput();
    void update();
    void render();
    void destory();
    int ticksLastFrame;

    static SDL_Renderer *renderer;
    void loadLevel(int levelNumber);

private:
    SDL_Window *m_window = nullptr;
    bool m_running = false;
};
