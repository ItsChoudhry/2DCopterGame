#include "Map.hpp"
#include "EntityManager.hpp"
#include "Game.hpp"
#include "components/TileComponent.hpp"
#include <fstream>

extern EntityManager manager;

Map::Map(std::string t_textureid, int t_scale, int t_tileSize)
{
    m_textureid = t_textureid;
    m_scale = t_scale;
    m_tileSize = t_tileSize;
}

void Map::loadMap(std::string t_filePath, int t_mapSizeX, int t_mapSizeY)
{
    std::fstream mapFile;
    mapFile.open(t_filePath);

    for (int y = 0; y < t_mapSizeY; y++)
    {
        for (int x = 0; x < t_mapSizeX; x++)
        {
            char ch;
            mapFile.get(ch);
            int sourceRectY = atoi(&ch) * m_tileSize;
            mapFile.get(ch);
            int sourceRectX = atoi(&ch) * m_tileSize;
            addTile(sourceRectX, sourceRectY, x * (m_scale * m_tileSize),
                    y * (m_scale * m_tileSize));
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::addTile(int t_sourceX, int t_sourceY, int t_x, int t_y)
{
    Entity &newTile(manager.addEntity("Tile"));
    newTile.addComponent<TileComponent>(t_sourceX, t_sourceY, t_x, t_y, m_tileSize,
                                        m_scale, m_textureid);
}
