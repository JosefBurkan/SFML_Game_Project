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
            sf::Texture iconTexture;
            
            int tileSize = 50;
            int movement = 5;

        public: 
            std::optional<sf::Sprite> sprite;  
            int healthPoints = 2;
            int maxHealth = healthPoints;
            int turn = 0;           // Hvor i lista starter uniten
            int currentOrder = 0;   // Hvor i lista er uniten hver runde
            int speed = 2;
            bool inMenu = false;          // Sjekk om menyen er åpen, eksisterer for å fortelle dette til andre klasser og brukes kun av player               

            std::string type = "unit";
            std::string name = "default";
            std::string state = "Neutral";  // Kun for player

            int framesUntilDraw = 20;
            int textureLocationY = 0;
            int textureLocationX = 0;

            // spritePath er for å kunne sette sprites til enheter når de opprettes
            Unit(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks);
            void spawn();
            void Move(float posX, float posY);
            virtual sf::Sprite GetIcon();
            std::pair<int, int> RetriveCoordinations();
            virtual void Draw(sf::RenderWindow& window);
            virtual void DrawUI(sf::RenderWindow& window);
            virtual void CheckForMapObjects();
            virtual void IsHit();
            virtual void PerformActions(); // Bevegelse, angrep, osv.. Men kun for fiender
            virtual void Movement();    // Bevegelse for spiller. Skal slå den sammen med 'PerformActions' etterhvert


    };
}
