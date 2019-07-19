#include "TextureManager.hpp"

SDL_Texture *TextureManager::loadTexture(const char *t_fileName)
{
    SDL_Surface *surface = IMG_Load(t_fileName);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::draw(SDL_Texture *t_texture, SDL_Rect t_sourceRectangle,
                          SDL_Rect t_destinationRectangle, SDL_RendererFlip t_flip)
{
    SDL_RenderCopyEx(Game::renderer, t_texture, &t_sourceRectangle,
                     &t_destinationRectangle, 0.0, nullptr, t_flip);
}
