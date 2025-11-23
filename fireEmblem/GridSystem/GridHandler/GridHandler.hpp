#pragma once
#include "../Tile/Tile.hpp"
#include "../GridGenerator/GridGenerator.hpp"

namespace MapObjects 
{
    class MapObject;
}

namespace GridHandlers
{
    class GridHandler
    {
        private:
            int movementCooldown = 0; // Sette en grense på hvor fort man kan bytte rute
            int selectedTileX = 0;    // Kordinat til valgt rute 
            int selectedTileY = 2;
            int coloredTileX = 0;     // Farge ruten når en karakter er valgt
            int coloredTileY = 0; 
            int rows = 0;
            int columns = 0;
            bool characterIsSelected;    // Er en karakter valgt?

            GridGenerators::GridGenerator& grid;

        public:
            int rangeX = 0;
            int rangeY = 0;
            GridHandler(GridGenerators::GridGenerator& gridGenerator);
            void Movement();
            void Attack();                                                  // Om spilleren angriper, erstatt "Movement" med "Attack"
            void MovementWhileSelected();                          // Bevegelseslogikken dersom en karakter er blitt valgt
            void HighlightMovement();
            std::pair<int, int> RetrieveTile() const;                       // Hent rute som spiller har valgt
            std::pair<float, float> SelectedTilePos();                      // Hent rute sin kordinater som spiller har valgt
            std::pair<int, int> RetrieveTileIndex();
            std::vector<std::vector<Tiles::Tile>>& RetrieveAllTiles();      // Hent alle ruter
            void SelectTile();
            void UnSelectTile();
            bool IsOccupied(Tiles::Tile tile);
            void RetrieveTileByPositions(float positionX, float positionY); // Sjekk om en rute er okkupert
            void CreateGrid(int r, int c);                                  // Generer gridden her
            void UpdateGrid();                                              // Sett hele rutefeltet tilbake til sin opprinnelige status
            void Draw(sf::RenderWindow& window); 
    };
}