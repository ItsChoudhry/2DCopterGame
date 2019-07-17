#pragma once

#include "EntityManager.hpp"
#include "FontManager.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>

class AssetManager
{
private:
    EntityManager *m_entityManager;
    std::map<std::string, SDL_Texture *> m_textures;
    std::map<std::string, TTF_Font *> m_fonts;

public:
    AssetManager(EntityManager *t_entityManager);
    ~AssetManager();
    void clearData();
    void addTexture(std::string t_textureID, const char *t_fileName);
    SDL_Texture *getTexture(std::string t_textureID);
    void addFont(std::string t_fontID, const char *t_fileName, int t_fontSize);
    TTF_Font *getFont(std::string t_fontID);
};
