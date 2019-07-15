#pragma once

#include "../EntityManager.hpp"
#include "../Game.hpp"
#include "SpirteComponent.hpp"
#include "TransformComponent.hpp"
#include <SDL2/SDL.h>

class KeyboardControlComponent : public Component
{
public:
    std::string upKey;
    std::string downKey;
    std::string leftKey;
    std::string rightKey;
    std::string shootKey;
    TransformComponent *m_transform;
    SpirteComponent *m_spirte;

    KeyboardControlComponent() {}

    KeyboardControlComponent(std::string t_upKey, std::string t_downKey,
                             std::string t_leftKey, std::string t_rightKey,
                             std::string t_shootKey)
    {
        upKey = getSDLKeyStringCode(t_upKey);
        downKey = getSDLKeyStringCode(t_downKey);
        leftKey = getSDLKeyStringCode(t_leftKey);
        rightKey = getSDLKeyStringCode(t_rightKey);
        shootKey = getSDLKeyStringCode(t_shootKey);
    }

    std::string getSDLKeyStringCode(std::string t_key)
    {
        if (t_key.compare("up") == 0)
            return "1073741906";
        if (t_key.compare("down") == 0)
            return "1073741905";
        if (t_key.compare("left") == 0)
            return "1073741904";
        if (t_key.compare("right") == 0)
            return "1073741903";
        if (t_key.compare("space") == 0)
            return "32";
        return std::to_string(static_cast<int>(t_key[0]));
    }

    void initialize() override
    {
        m_transform = owner->getComponent<TransformComponent>();
        m_spirte = owner->getComponent<SpirteComponent>();
    }

    void update(float t_deltaTime) override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);

            if (keyCode.compare(upKey) == 0)
            {
                m_transform->velocity.y = -100;
                m_transform->velocity.x = 0;
                m_spirte->play("UpAnimation");
            }
            if (keyCode.compare(downKey) == 0)
            {
                m_transform->velocity.y = 100;
                m_transform->velocity.x = 0;
                m_spirte->play("DownAnimation");
            }
            if (keyCode.compare(leftKey) == 0)
            {
                m_transform->velocity.y = 0;
                m_transform->velocity.x = -100;
                m_spirte->play("LeftAnimation");
            }
            if (keyCode.compare(rightKey) == 0)
            {
                m_transform->velocity.y = 0;
                m_transform->velocity.x = 100;
                m_spirte->play("RightAnimation");
            }
            if (keyCode.compare(shootKey) == 0)
            {
            }
        }

        if (Game::event.type == SDL_KEYUP)
        {
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);

            if (keyCode.compare(upKey) == 0)
            {
                m_transform->velocity.y = 0;
            }
            if (keyCode.compare(downKey) == 0)
            {
                m_transform->velocity.y = 0;
            }
            if (keyCode.compare(leftKey) == 0)
            {
                m_transform->velocity.x = 0;
            }
            if (keyCode.compare(rightKey) == 0)
            {
                m_transform->velocity.x = 0;
            }
        }
    }

private:
};
