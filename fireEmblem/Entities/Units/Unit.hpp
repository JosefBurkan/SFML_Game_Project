#pragma once
#include "../../config.hpp"
#include "../../GridSystem/GridMovement/GridMovement.hpp"
#include "../../GridSystem/GridGenerator/GridGenerator.hpp"

namespace Units 
{
    class Unit 
    {
        protected:  
            GridGenerators::GridGenerator& gridGenerator;
            sf::Texture texture;
            std::optional<sf::Sprite> sprite;  
            std::string name;
            int healthPoints;
            std::string spritePath;
            
        public: 
            // spritePath er for å kunne sette sprites til enheter når de opprettes
            Unit(std::string name, int healthPoints, std::string spritePath, GridGenerators::GridGenerator& gridReference);
            void spawn();
            std::pair<int, int> RetriveCoordinations();
    };
}
