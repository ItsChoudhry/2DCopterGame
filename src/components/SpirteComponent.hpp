#pragma once

#include "../Animation.hpp"
#include "../AssetManager.hpp"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <string>

class SpirteComponent : public Component
{
private:
    TransformComponent *m_transform;
    SDL_Texture *m_texture;
    SDL_Rect m_sourceRectangle;
    SDL_Rect m_destinationRectangle;
    bool m_isAnimated;
    int m_numFrames;
    int m_animationSpeed;
    bool m_isFixed;
    std::map<std::string, Animation> m_animations;
    std::string m_currentAnimationName;
    unsigned int m_animationIndex = 0;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpirteComponent(std::string t_assetTextureID)
    {
        m_isAnimated = false;
        m_isFixed = false;
        setTexture(t_assetTextureID);
    }

    SpirteComponent(std::string t_id, int t_numFrames, int t_animationSpped,
                    bool t_hasDirection, bool t_isFixed)
    {
        m_isAnimated = true;
        m_numFrames = t_numFrames;
        m_animationSpeed = t_animationSpped;
        m_isFixed = t_isFixed;

        if (t_hasDirection)
        {
            Animation downAnimation = Animation(0, m_numFrames, m_animationSpeed);
            Animation rightAnimation = Animation(1, m_numFrames, m_animationSpeed);
            Animation leftAnimation = Animation(2, m_numFrames, m_animationSpeed);
            Animation upAnimation = Animation(3, m_numFrames, m_animationSpeed);

            m_animations.emplace("DownAnimation", downAnimation);
            m_animations.emplace("RightAnimation", rightAnimation);
            m_animations.emplace("LeftAnimation", leftAnimation);
            m_animations.emplace("UpAnimation", upAnimation);

            m_animationIndex = 0;
            m_currentAnimationName = "DownAnimation";
        }
        else
        {
            Animation singleAnimation = Animation(0, m_numFrames, m_animationSpeed);
            m_animations.emplace("SingleAnimation", singleAnimation);
            m_animationIndex = 0;
            m_currentAnimationName = "SingleAnimation";
        }

        play(m_currentAnimationName);
        setTexture(t_id);
    }

    void play(std::string t_animationName)
    {
        m_numFrames = m_animations[t_animationName].numFrames;
        m_animationIndex = m_animations[t_animationName].index;
        m_animationSpeed = m_animations[t_animationName].animationSpeed;
        m_currentAnimationName = t_animationName;
    }

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
        if (m_isAnimated)
        {
            m_sourceRectangle.x =
                m_sourceRectangle.w *
                static_cast<int>((SDL_GetTicks() / m_animationSpeed) % m_numFrames);
        }
        m_sourceRectangle.y = m_animationIndex * m_transform->height;

        m_destinationRectangle.x = static_cast<int>(m_transform->position.x) -
                                   (m_isFixed ? 0 : Game::camera.x);
        m_destinationRectangle.y = static_cast<int>(m_transform->position.y) -
                                   (m_isFixed ? 0 : Game::camera.y);
        m_destinationRectangle.w = m_transform->width * m_transform->scale;
        m_destinationRectangle.h = m_transform->height * m_transform->scale;
    }

    void render() override
    {
        TextureManager::draw(m_texture, m_sourceRectangle, m_destinationRectangle,
                             spriteFlip);
    }
};
