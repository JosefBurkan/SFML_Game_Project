#include "../GridGenerator/GridGenerator.cpp"
#pragma once
using namespace GridGenerators;

namespace GridMovements
{
    class GridMovement
    {

        private:
            int movementCooldown = 0; // Sette en grense på hvor fort man kan bytte rute
            int selectedTileX = 0;    // Kordinat til valgt rute 
            int selectedTileY = 0;
            int coloredTileX = 0;     // Farge ruten når en karakter er valgt
            int coloredTileY = 0; 
            int rows = 0;
            int columns = 0;
            GridGenerator& grid;

        public:

            GridMovement(GridGenerator& gridGenerator)
                : grid(gridGenerator)
            {
                auto& tiles = grid.RetrieveAllTiles();
                rows = tiles.size();
                columns = tiles[0].size();
            }
            
            void Movement() {
                auto& tiles = grid.RetrieveAllTiles();

                int prevX = selectedTileX;
                int prevY = selectedTileY;

                if (movementCooldown > 2) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && selectedTileX < columns - 1) {
                        selectedTileX++;
                    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && selectedTileX > 0) {
                        selectedTileX--;
                    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && selectedTileY < rows - 1) {
                        selectedTileY++;
                    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && selectedTileY > 0) {
                        selectedTileY--;
                    }

                movementCooldown = 0;

                } else 
                {
                    movementCooldown++;
                }

                if (prevX != selectedTileX || prevY != selectedTileY) {
                    tiles[prevY][prevX].ChangeColor(false);
                    tiles[selectedTileY][selectedTileX].ChangeColor(true);
                }
            }

            // Hent rute som spiller har valgt
            std::pair<int, int> RetrieveTile() const {
                return {selectedTileX, selectedTileY};
            }

            // Hent rute sin kordinater som spiller har valgt
            std::pair<float, float> SelectedTilePos() 
            {
                auto& tiles = grid.RetrieveAllTiles();

                return {tiles[selectedTileY][selectedTileX].RetrieveTilePos().first, 
                        tiles[selectedTileY][selectedTileX].RetrieveTilePos().second};
            }

            // Hent alle ruter
            std::vector<std::vector<Tile>>& RetrieveAllTiles()
            {
                auto& tiles = grid.RetrieveAllTiles();
                return tiles;
            }

            void SelectTile()
            {
                auto& tiles = grid.RetrieveAllTiles();
                coloredTileX = selectedTileX;
                coloredTileY = selectedTileY;

                tiles[coloredTileY][coloredTileX].Select();
            }

            void UnSelectTile()
            {
                auto& tiles = grid.RetrieveAllTiles();
                coloredTileX = selectedTileX;
                coloredTileY = selectedTileY;

                tiles[coloredTileY][coloredTileX].UnSelect();
            }

            void PrintGrid()
            {
                auto& tiles = grid.RetrieveAllTiles();
                cout << tiles[3][3].RetrieveTilePos().first;
            }
    };
}