#include "FontManager.hpp"
#include <iostream>

TTF_Font *FontManager::loadFont(const char *t_fileName, int t_fontSize)
{
    return TTF_OpenFont(t_fileName, t_fontSize);
}

void FontManager::draw(SDL_Texture *t_texture, SDL_Rect t_position)
{
    SDL_RenderCopy(Game::renderer, t_texture, NULL, &t_position);
}
