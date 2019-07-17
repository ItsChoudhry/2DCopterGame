#include "AssetManager.hpp"

AssetManager::AssetManager(EntityManager *t_entityManger)
    : m_entityManager(t_entityManger)
{
}

void AssetManager::clearData()
{
    m_textures.clear();
    m_fonts.clear();
}

void AssetManager::addTexture(std::string t_textureID, const char *t_fileName)
{
    m_textures.emplace(t_textureID, TextureManager::loadTexture(t_fileName));
}

SDL_Texture *AssetManager::getTexture(std::string t_textureID)
{
    return m_textures[t_textureID];
}

void AssetManager::addFont(std::string t_fontID, const char *t_fileName, int t_fontSize)
{
    m_fonts.emplace(t_fontID, FontManager::loadFont(t_fileName, t_fontSize));
}

TTF_Font *AssetManager::getFont(std::string t_fontID) { return m_fonts[t_fontID]; }
