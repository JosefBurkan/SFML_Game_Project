#pragma once
#include "../../config.hpp"
#include "../../GridSystem/GridGenerator/GridGenerator.hpp"
#include "../../Maps/MapLayouts/Map/Map.hpp"
#include "../../Hitboxes/Attacks/AttackManager/AttackManager.hpp"

namespace Units 
{
    class Unit 
    {
        protected:  
            GridGenerators::GridGenerator& gridGenerator;
            AttackManagers::AttackManager& attacks;
            Maps::Map& map;
            sf::Texture texture;
            std::string spritePath;
            int tileSize = 50;
            int movement = 5;
            
        public: 
            std::optional<sf::Sprite> sprite;  
            std::string type = "unit";
            int healthPoints = 2;
            int maxHealth = healthPoints;
            int turn = 0;
            std::string name = "default";
            int speed = 2;

            // spritePath er for å kunne sette sprites til enheter når de opprettes
            Unit(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks);
            void spawn();
            std::pair<int, int> RetriveCoordinations();
            virtual void Draw(sf::RenderWindow& window);
            virtual void CheckForMapObjects();
            virtual void IsHit();
            virtual void PerformActions(); // Bevegelse, angrep, osv.. Men kun for fiender


    };
}
