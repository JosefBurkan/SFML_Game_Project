#include "Background1.hpp"
#include <fstream>
#include <sstream> 

namespace Backgrounds1
{

    Background1::Background1(GridHandlers::GridHandler& GridHandler)
        : movement(GridHandler)
    {
    }

    // Les tilemap-fila
    bool Background1::LoadTileMapFromFile() 
    {
        auto& tiles = movement.RetrieveAllTiles();

        if (!m_tileset.loadFromFile(std::string(ASSETS_DIR) + "Tileset1.png"))
            return false;

        ReadTileFile();

        // Endre størrelsen på vertex array til å passe banen
        m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        m_vertices.resize(tiles.size() * tiles[0].size() * 6);

        // Fyll vertex arrayen med to triangler per tile
        for (unsigned int i = 0; i < tiles.size(); ++i)
        {
            for (unsigned int j = 0; j < tiles[0].size(); ++j)
            {
                std::cout << tiles[i][j].tileNumber;
                const int tileNumber = tiles[i][j].tileNumber;

                // Koble tilenummeret til riktig texture fra bildet
                const int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                const int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the triangles' vertices of the current tile
                sf::Vertex* triangles = &m_vertices[(i + j * tiles.size()) * 6];

                // define the 6 corners of the two triangles
                triangles[0].position = sf::Vector2f(j * tileSize.x, i * tileSize.y);
                triangles[1].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
                triangles[2].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);
                triangles[3].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);
                triangles[4].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
                triangles[5].position = sf::Vector2f((j + 1) * tileSize.x, (i + 1) * tileSize.y);

                // define the 6 matching texture coordinates
                triangles[0].texCoords = sf::Vector2f(tu * tileSize.y, tv * tileSize.x);
                triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.y, tv * tileSize.x);
                triangles[2].texCoords = sf::Vector2f(tu * tileSize.y, (tv + 1) * tileSize.x);
                triangles[3].texCoords = sf::Vector2f(tu * tileSize.y, (tv + 1) * tileSize.x);
                triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.y, tv * tileSize.x);
                triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.y, (tv + 1) * tileSize.x);
            }
        }

        return true;
    }

    // Les, og sett ruteadressene til å bli likt det i .txt fila til bakgrunnen
    void Background1::ReadTileFile()
    {
        auto& tiles = movement.RetrieveAllTiles();
                
        std::ifstream file(std::string(ASSETS_DIR) + "Background_One.txt");
        std::string line;
        int row = 0;

        while (std::getline(file, line)) {
            std::istringstream ss(line);
            int tileNumber;
            int col = 0;

            while (ss >> tileNumber && col < columns) 
            {
                tiles[row][col].tileNumber = tileNumber;
                ++col;
            }
            ++row;
        }
    }

    void Background1::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }
}