#pragma once
#include "../../../config.hpp"
#include "../Unit.hpp"
#include "../../../GridSystem/GridMovement/GridMovement.hpp"
#include "../../../Maps/MapLayouts/Map/Map.hpp"

namespace GridGenerators 
{
    class GridGenerator;
}

namespace Players 
{
    class Player : public Units::Unit 
    {

        private:
            
            GridMovements::GridMovement& gridMovement;          // Funksjonalitet for bevegelse
            int playerCurrentTileX = 0;
            int playerCurrentTileY = 0;
            bool isSelected = false;                            // Sjekk om spilleren har blitt valgt
            bool preventSelect = false;                         // Forebygg at spilleren kan velges
            sf::Vector2f realTimePos = sprite->getPosition();   // Hent spilleren sin posisjon

        public:
            Player(GridGenerators::GridGenerator& gridReference, Maps::Map& map, GridMovements::GridMovement& gridMovement);
            void Movement();
    };
}


