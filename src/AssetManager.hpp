#pragma once

#include "EntityManager.hpp"
#include "TextureManager.hpp"
#include <map>
#include <string>

class AssetManager
{
private:
    EntityManager *m_entityManager;
    std::map<std::string, SDL_Texture *> m_textures;

public:
    AssetManager(EntityManager *t_entityManager);
    ~AssetManager();
    void clearData();
    void addTexture(std::string t_textureID, const char *t_fileName);
    SDL_Texture *getTexture(std::string t_textureID);
};
