#pragma once

#include "../AssetManager.hpp"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include <SDL2/SDL.h>

class SpirteComponent : public Component
{
private:
    TransformComponent *m_transform;
    SDL_Texture *m_texture;
    SDL_Rect m_sourceRectangle;
    SDL_Rect m_destinationRectangle;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpirteComponent(const char *t_filePath) { setTexture(t_filePath); }

    void setTexture(std::string t_assetTextureID)
    {
        m_texture = Game::assetManager->getTexture(t_assetTextureID);
    }

    void initialize() override
    {
        m_transform = owner->getComponent<TransformComponent>();
        m_sourceRectangle.x = 0;
        m_sourceRectangle.y = 0;
        m_sourceRectangle.w = m_transform->width;
        m_sourceRectangle.h = m_transform->height;
    }

    void update(float t_deltaTime) override
    {
        m_destinationRectangle.x = static_cast<int>(m_transform->position.x);
        m_destinationRectangle.y = static_cast<int>(m_transform->position.y);
        m_destinationRectangle.w = m_transform->width * m_transform->scale;
        m_destinationRectangle.h = m_transform->height * m_transform->scale;
    }

    void render() override
    {
        TextureManager::draw(m_texture, m_sourceRectangle, m_destinationRectangle,
                             spriteFlip);
    }
};
