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

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool m_running;
};
