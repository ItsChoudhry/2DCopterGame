#pragma once

#include "Game.hpp"

class TextureManager
{
public:
    static SDL_Texture *loadTexture(const char *t_fileName);
    static void draw(SDL_Texture *t_texture, SDL_Rect t_sourceRectangle,
                     SDL_Rect t_destinationRectangle, SDL_RendererFlip t_flip);
};
