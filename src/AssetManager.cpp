#include "AssetManager.hpp"

AssetManager::AssetManager(EntityManager *t_entityManger)
    : m_entityManager(t_entityManger)
{
}

void AssetManager::clearData() { m_textures.clear(); }

void AssetManager::addTexture(std::string t_textureID, const char *t_fileName)
{
    m_textures.emplace(t_textureID, TextureManager::loadTexture(t_fileName));
}

SDL_Texture *AssetManager::getTexture(std::string t_textureID)
{
    return m_textures[t_textureID];
}
