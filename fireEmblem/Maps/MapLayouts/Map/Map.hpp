#pragma once
#include "../../../GridSystem/GridGenerator/GridGenerator.hpp"
#include "../../../config.hpp"
#include "../../../Entities/MapObjects/MapObject.hpp"
#include "../../../Entities/MapObjects/Bat/Bat.hpp"
#include "../../../Entities/MapObjects/Wall/Wall.hpp"
#include "../../../GridSystem/GridHandler/GridHandler.hpp"

namespace Maps 
{

    class Map 
    {
        public:
            sf::Texture wallTexture;
            sf::RenderWindow window;
            std::vector<MapObjects::MapObject> mapObjects;
            std::vector<Walls::Wall> walls;

            unsigned int numberOfColumns = 15;
            unsigned int numberOfRows = 16;
            GridGenerators::GridGenerator gridGenerator;
            GridHandlers::GridHandler* GridHandlerPtr = nullptr;

            // Baneobjekter
            Bats::Bat mapObject2;

            Map();
            
            void GenerateGrid();
            GridGenerators::GridGenerator& FetchGrid();                     // returner gridGenerator med verdiene til den eksisterende gridden
            void SetGridHandler(GridHandlers::GridHandler& movement);    // Hent inn GridHandler, for å lese og påvirke rutefeltet
            void LoadWindow();
            sf::View LoadView();                                            // Last inn kameraet
            void SpawnObjects();                                          // Sett objektet sin posisjon
            void DrawMapObjects(sf::RenderWindow& window);                  // Tegn baneobjekter, feks. trær

    };
}