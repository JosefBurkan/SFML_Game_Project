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
            sf::Texture defaultTexture;
            sf::Texture attackTexture;      // Animasjon for når en karakter angriper
            std::string spritePath;
            sf::Texture iconTexture;
            
            int tileSize = 50;
            int movement = 5;
            int spriteSizeY = 50;     // Hvor mange pixler animasjonen skal være
            int spriteSizeX = 100;
            int drawSpeed = 20;

        public: 
            std::optional<sf::Sprite> sprite;
            std::optional<sf::Sprite> attackSprite;  
            int healthPoints = 2;
            int maxHealth = healthPoints;
            int turn = 0;           // Hvor i lista starter uniten
            int currentOrder = 0;   // Hvor i lista er uniten hver runde
            int speed = 2;
            int attackTimer = 24;   // Hvor lenge angrepsanimasjonen til uniten varer
            int maxAttackTimer = 24;
            int attackSpawnTimer = 16;   // Når angrepet (hitboxen) skal lages

            bool inMenu = false;          // Sjekk om menyen er åpen, eksisterer for å fortelle dette til andre klasser og brukes kun av player               

            std::string type = "unit";
            std::string name = "default";
            std::string state = "Neutral";  // Kun for player

            int framesUntilDraw = 20;
            int defaultTextureY = 0;    // Lokasjonen til defaultsprite
            int defaultTextureX = 0;

            int attackingTextureY = 0;  // Lokasjonen til attacksprite
            int attackingTextureX = 0;

            // spritePath er for å kunne sette sprites til enheter når de opprettes
            Unit(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks);
            void spawn();
            void Move(float posX, float posY);
            virtual sf::Sprite GetIcon();
            std::pair<int, int> RetriveCoordinations();
            virtual void SetTileToOccupied();
            virtual void SetTileToUnOccupied();
            virtual void Draw(sf::RenderWindow& window);    // Default animasjon
            virtual void DrawUI(sf::RenderWindow& window);
            virtual void DrawAttackAnimation(sf::RenderWindow& window); // Når de angriper
            virtual void CheckForMapObjects();
            virtual void IsHit();
            virtual void PerformActions(); // Bevegelse, angrep, osv.. Men kun for fiender
            virtual void Movement();    // Bevegelse for spiller. Skal slå den sammen med 'PerformActions' etterhvert
            virtual void ResetAnimations(); // Set animasjoner tilbake til starten, slik at de ikke kan starte midt i
    };
}
