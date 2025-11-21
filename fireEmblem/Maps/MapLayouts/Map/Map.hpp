#pragma once
#include "../../../GridSystem/GridGenerator/GridGenerator.hpp"
#include "../../../config.hpp"
#include "../../../Entities/MapObjects/Tree/Tree.hpp"
#include "../../../Entities/MapObjects/Wall/Wall.hpp"
#include "../../../GridSystem/GridHandler/GridHandler.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/GridHandler/GridHandler.hpp"

namespace Maps 
{

    class Map 
    {
        public:
            sf::Texture wallTexture;
            sf::Texture treeTexture;
            sf::RenderWindow window;
            std::vector<Trees::Tree> trees;
            std::vector<Walls::Wall> walls;

            unsigned int numberOfColumns = 15;
            unsigned int numberOfRows = 16;
            GridGenerators::GridGenerator gridGenerator;
            GridHandlers::GridHandler* GridHandlerPtr = nullptr;

            Map();
            
            void GenerateGrid();
            GridGenerators::GridGenerator& FetchGrid();                     // returner gridGenerator med verdiene til den eksisterende gridden
            void SetGridMovement(GridHandlers::GridHandler& movement);    // Hent inn GridHandler, for å lese og påvirke rutefeltet
            void LoadWindow();
            sf::View LoadView();                                            // Last inn kameraet
            void SpawnObjects();                                          // Sett objektet sin posisjon
            void DrawMapObjects(sf::RenderWindow& window);                  // Tegn baneobjekter, feks. trær

    };
}