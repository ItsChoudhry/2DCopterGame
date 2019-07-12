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
        m_texture = Game::assetManager->getTexture(t_assetTextureID);
        m_sourceRect.x = t_sourceRectX;
        m_sourceRect.y = t_sourceRectY;
        m_sourceRect.w = t_tileSize;
        m_sourceRect.h = t_tileSize;

        m_destinationRect.x = t_x;
        m_destinationRect.y = t_y;
        m_destinationRect.w = t_tileSize * t_tileScale;
        m_destinationRect.h = t_tileSize * t_tileScale;

        m_position.x = t_x;
        m_position.y = t_y;
    }
    ~TileComponent() { SDL_DestroyTexture(m_texture); }

    void update(float t_deltaTime) override
    {
        m_destinationRect.x = m_position.x - Game::camera.x;
        m_destinationRect.y = m_position.y - Game::camera.y;
    }

    void render() override
    {
        TextureManager::draw(m_texture, m_sourceRect, m_destinationRect, SDL_FLIP_NONE);
    }
};
