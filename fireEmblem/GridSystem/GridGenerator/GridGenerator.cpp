#include "GridGenerator.hpp"

namespace GridGenerators
{
    void GridGenerator::CreateGrid(int r, int c) 
    {
        rows = r;
        columns = c;

        // Lag plass for hver rad
        tiles.resize(rows);

        for (int row = 0; row < rows; row++) 
        {
            // Lag plass for hver kolonne
            tiles[row].resize(columns);

            for (int column = 0; column < columns; column++)
            {

                // Avstanden mellom hver tile. 50.f = areal til rute
                float rowX = column * 50.f;
                float rowY = row * 50.f;

                tiles[row][column] = Tiles::Tile(rowX, rowY); // Bygg en rute med tilsvarende kordinater
            }
        }
        tiles[0][0].ChangeColor(true);
    }

    // Hent alle ruter
    std::vector<std::vector<Tiles::Tile>>& GridGenerator::RetrieveAllTiles()
    {
        return tiles;
    }

    void GridGenerator::Draw(sf::RenderWindow& window) 
    {
        for (int row = 0; row < rows; row++)
        {

            for (int column = 0; column < columns; column++)
            {
                if (row == selectedTileY && column == selectedTileX)
                    continue; // Ignorer den valgte ruten

                tiles[row][column].Draw(window);
            }
        }
        tiles[selectedTileY][selectedTileX].Draw(window);
    }


}