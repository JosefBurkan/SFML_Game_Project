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
            std::optional<sf::Sprite> sprite;  
            std::string spritePath;

            std::string name = "default";
            int movement = 5;
            
        public: 
            std::string type = "unit";
            int healthPoints = 2;
            bool currentTurn = true;

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
