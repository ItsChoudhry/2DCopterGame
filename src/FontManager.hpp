#pragma once

#include "Game.hpp"
#include <SDL2/SDL_ttf.h>

class FontManager
{
public:
    static TTF_Font *loadFont(const char *t_fileName, int fontSize);
    static void draw(SDL_Texture *t_texture, SDL_Rect t_position);
};
