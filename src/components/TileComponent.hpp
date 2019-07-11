#pragma once

#include "../../lib/glm/glm.hpp"
#include "../AssetManager.hpp"
#include "../EntityManager.hpp"
#include <SDL2/SDL.h>

class TileComponent : public Component
{
private:
public:
    SDL_Texture *m_texture;
    SDL_Rect m_sourceRect;
    SDL_Rect m_destinationRect;
    glm::vec2 m_position;

    TileComponent(int t_sourceRectX, int t_sourceRectY, int t_x, int t_y,
                  int t_tileSize, int t_tileScale, std::string t_assetTextureID)
    {
    }
    ~TileComponent() { SDL_DestroyTexture(m_texture); }

    void update(float t_deltaTime) override {}

    void render() override
    {
        TextureManager::draw(m_texture, m_sourceRect, m_destinationRect, SDL_FLIP_NONE)
    }
};
