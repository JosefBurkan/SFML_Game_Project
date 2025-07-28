#pragma once
#include "../../../config.hpp"
#include "../Unit.hpp"
#include "../../../GridSystem/GridMovement/GridMovement.hpp"
#include "../../../Maps//Map/Map.hpp"

namespace GridGenerators 
{
    class GridGenerator;
}

namespace Players 
{
    class Player : public Units::Unit 
    {

        private:

            Maps::Map& map;
            GridMovements::GridMovement& gridMovement;          // Funksjonalitet for bevegelse
            int playerCurrentTileX = 0;
            int playerCurrentTileY = 0;
            bool isSelected = false;                            // Sjekk om spilleren har blitt valgt
            bool preventSelect = false;                         // Forebygg at spilleren kan velges
            sf::Vector2f realTimePos = sprite->getPosition();   // Hent spilleren sin posisjon

        public:
            Player(std::string name, int healthPoints, std::string spritePath, GridGenerators::GridGenerator& gridReference, GridMovements::GridMovement& gridMovement, Maps::Map& map);
            void Draw(sf::RenderWindow& window);
            void Movement();
            void CheckForMapObjects();
    };
}


