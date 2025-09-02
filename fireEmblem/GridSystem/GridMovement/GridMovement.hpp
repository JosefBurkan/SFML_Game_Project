#pragma once
#include "../GridGenerator/GridGenerator.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/Tile/Tile.hpp"

namespace GridMovements
{
    class GridMovement
    {

        int movementCooldown = 0;  // Sette en grense på hvor fort man kan bytte rute
        int selectedTileX = 0;     // Kordinat til valgt rute 
        int selectedTileY = 0;
        int coloredTileX = 0;      // Farge ruten når en karakter er valgt
        int coloredTileY = 0; 
        int rows = 0;
        int columns = 0;

        GridGenerators::GridGenerator& grid;

        public:
            int rangeX = 0;
            int rangeY = 0;
            GridMovement(GridGenerators::GridGenerator& gridGenerator);
            void Movement();
            void Attack();                                                  // Om spilleren angriper, erstatt "Movement" med "Attack"
            void MovementWhileSelected();                          // Bevegelseslogikken dersom en karakter er blitt valgt

            std::vector<std::vector<Tiles::Tile>>& RetrieveAllTiles();      // Hent alle ruter
    };
}