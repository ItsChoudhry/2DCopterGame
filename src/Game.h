#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game
{
public:
    Game();
    bool isRunning() const;
    void initialize(int t_width, int t_height);
    void processInput();
    void update();
    void render();
    void destory();
    float projectilePosX = 0.0f;
    float projectilePosY = 0.0f;
    float projectileVelX = 0.5f;
    float projectileVelY = 0.5f;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool m_running;
};
