#pragma once
#include "../Tile/Tile.hpp"
#include "../GridGenerator/GridGenerator.hpp"

namespace MapObjects 
{
    class MapObject;
}

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
            GridGenerators::GridGenerator& grid;

        public:

            GridMovement(GridGenerators::GridGenerator& gridGenerator);

            void Movement();

            // Hent rute som spiller har valgt
            std::pair<int, int> RetrieveTile() const;

            // Hent rute sin kordinater som spiller har valgt
            std::pair<float, float> SelectedTilePos();

            // Hent alle ruter
            std::vector<std::vector<Tiles::Tile>>& RetrieveAllTiles();

            void SelectTile();

            void UnSelectTile();

            // Sjekk om en rute er okkupert
            bool IsOccupied(Tiles::Tile tile);
            void RetrieveTileByPositions(float positionX, float positionY);

            // TEST: Print en tile sine koordinater
            void PrintGrid();



    };
}