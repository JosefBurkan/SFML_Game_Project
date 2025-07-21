#pragma once
#include "../Tile/Tile.hpp"

namespace GridGenerators
{
    class GridGenerator
    {

        public:
        std::vector<std::vector<Tiles::Tile>> tiles;
        Tiles::Tile tile{0, 0};
        int selectedTileX = 0;    // Kordinat til valgt rute 
        int selectedTileY = 0;
        int rows = 0;
        int columns = 0;

        void CreateGrid(int r, int c);

        // Hent alle ruter
        std::vector<std::vector<Tiles::Tile>>& RetrieveAllTiles();

        void Draw(sf::RenderWindow& window); 


    };

}