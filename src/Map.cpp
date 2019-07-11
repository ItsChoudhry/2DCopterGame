#include "Map.hpp"
#include "EntityManager.hpp"
#include "Game.hpp"

Map::Map(std::string t_textureid, int t_scale, int t_tileSize)
{
    m_textureid = t_textureid;
    m_scale = t_scale;
    m_tileSize = t_tileSize;
}

void Map::loadMap(std::string t_filePath, int t_SizeX, int t_mapSizeY)
{
    // TODO
}

void Map::addTile(int t_sourceX, int t_sourceY, int t_x, int t_y)
{
    // TODO
}
