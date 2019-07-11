#pragma once

#include <string>

class Map
{
private:
    std::string m_textureid;
    int m_scale;
    int m_tileSize;

public:
    Map(std::string t_textureid, int t_scale, int t_tileSize);
    ~Map();
    void loadMap(std::string t_filePath, int t_SizeX, int t_mapSizeY);
    void addTile(int t_sourceX, int t_sourceY, int t_x, int t_y);
};
