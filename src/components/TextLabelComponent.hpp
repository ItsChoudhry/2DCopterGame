#pragma once

#include "../AssetManager.hpp"
#include "../EntityManager.hpp"
#include "../FontManager.hpp"
#include "../Game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

class TextLabelComponent : public Component
{
private:
    SDL_Rect m_position;
    std::string m_text;
    std::string m_fontFamily;
    SDL_Color m_color;
    SDL_Texture *m_texture;

public:
    TextLabelComponent(int t_x, int t_y, std::string t_text, std::string t_fontFamily,
                       const SDL_Color &t_color)
    {
        m_position.x = t_x;
        m_position.y = t_y;
        m_text = t_text;
        m_fontFamily = t_fontFamily;
        m_color = t_color;
        setLabelText(m_text, m_fontFamily);
    }

    void setLabelText(std::string t_text, std::string t_fontFamily)
    {
        SDL_Surface *surface = TTF_RenderText_Blended(
            Game::assetManager->getFont(t_fontFamily), t_text.c_str(), m_color);
        m_texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(m_texture, NULL, NULL, &m_position.w, &m_position.h);
    }

    void render() override { FontManager::draw(m_texture, m_position); }
};
