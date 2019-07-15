#pragma once

#include <SDL2/SDL.h>

class Collision
{
private:
    /* data */
public:
    static bool checkRectCollision(const SDL_Rect &t_RectA, const SDL_Rect &t_RectB);
};
