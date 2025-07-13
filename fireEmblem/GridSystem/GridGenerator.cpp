#include "Tile.cpp"
#include <vector>
using namespace Tiles;
#pragma once

namespace GridGenerators
{
    class GridGenerator
    {
        // std::vector<Tile> tiles;
        std::vector<std::vector<Tile>> tiles;


        public:

        Tile tile{0, 0};

        int movementCooldown = 0; // Sette en grense på hvor fort man kan bytte rute
        int selectedTileX = 0;    // Kordinat til valgt rute 
        int selectedTileY = 0;
        int coloredTileX = 0;     // Farge ruten når en karakter er valgt
        int coloredTileY = 0; 
        int rows = 0;
        int columns = 0;
        bool isColumnBigger;        // Om det er fler kolonner enn rader, set til true

        void CreateGrid(int r, int c) 
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

                // Avstanden mellom hver tile. Burde være like stor som en tile sin størrelse
                // For øyeblikket hardkodet. Burde endres
                float rowX = column * 50.f;
                float rowY = row * 50.f;

                tiles[row][column] = Tile(rowX, rowY); // Bygg en rute med tilsvarende kordinater
                }
            }
        

            // Farg første rute
            tiles[0][0].ChangeColor(true);
        }


        void Movement() {
            int prevX = selectedTileX;
            int prevY = selectedTileY;

            if (movementCooldown > 1) {
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
            return {tiles[selectedTileY][selectedTileX].RetrieveTilePos().first, 
                    tiles[selectedTileY][selectedTileX].RetrieveTilePos().second};
        }

        // Hent alle ruter
        const std::vector<std::vector<Tile>>& RetrieveAllTiles() const
        {
            return tiles;
        }


    
        void SelectTile()
        {
            coloredTileX = selectedTileX;
            coloredTileY = selectedTileY;

            tiles[coloredTileY][coloredTileX].Select();
        }

        void Draw(sf::RenderWindow& window) 
        {

            Movement();

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

    };

}