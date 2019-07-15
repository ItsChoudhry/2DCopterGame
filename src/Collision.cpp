#include "Collision.hpp"

bool Collision::checkRectCollision(const SDL_Rect &t_RectA, const SDL_Rect &t_RectB)
{
    return (t_RectA.x + t_RectA.w >= t_RectB.x && t_RectB.x + t_RectB.w >= t_RectA.x &&
            t_RectA.y + t_RectA.h >= t_RectB.y && t_RectB.y + t_RectB.h >= t_RectA.y);
}
