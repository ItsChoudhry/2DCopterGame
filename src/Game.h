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
    int ticksLastFrame;
    float projectilePosX = 0.0f;
    float projectilePosY = 0.0f;
    float projectileVelX = 20.0f;
    float projectileVelY = 30.0f;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool m_running;
};
