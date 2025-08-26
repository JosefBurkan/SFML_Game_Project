#include "Background1.hpp"
#include <fstream>
#include <sstream> 

namespace Backgrounds1
{

    Background1::Background1(GridHandlers::GridHandler& GridHandler)
        :movement(GridHandler)
    {
    }

    void Background1::Draw(sf::RenderWindow& window)
    {
        auto& tiles = movement.RetrieveAllTiles();

        for (int row = 0; row < tiles.size(); row++)
        {
            for (int column = 0; column < tiles[row].size(); column++)
            {
                backgroundTile.sprite->setPosition({1.f * column * 50, 1.f * row * 50});
                backgroundTile.Draw(window);
                backgroundTile.ChangeTile(tiles[row][column].tileNumber);
            }
        }
    }

    // Les 
    void Background1::LoadTileMapFromFile() 
    {

        auto& tiles = movement.RetrieveAllTiles();
        std::ifstream file("Background_One.txt");
        std::string line;
        int row = 0;

        while (std::getline(file, line)) {
            std::istringstream ss(line);
            int tileNumber;
            int col = 0;

            while (ss >> tileNumber) {
                tiles[row][col].tileNumber = tileNumber;
                ++col;
            }
            ++row;
        }
    }

}