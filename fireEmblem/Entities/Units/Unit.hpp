#pragma once
#include "../../config.hpp"
#include "../../GridSystem/GridGenerator/GridGenerator.hpp"
#include "../../Maps/MapLayouts/Map/Map.hpp"

namespace Units 
{
    class Unit 
    {
        protected:  
            GridGenerators::GridGenerator& gridGenerator;
            Maps::Map& map;
            sf::Texture texture;
            std::optional<sf::Sprite> sprite;  
            std::string name = "default";
            int healthPoints = 5;
            int movement = 5;
            std::string spritePath;
            
        public: 
            // spritePath er for å kunne sette sprites til enheter når de opprettes
            Unit(GridGenerators::GridGenerator& gridReference, Maps::Map& map);
            void spawn();
            std::pair<int, int> RetriveCoordinations();
            void Draw(sf::RenderWindow& window);
            void CheckForMapObjects();


    };
}
