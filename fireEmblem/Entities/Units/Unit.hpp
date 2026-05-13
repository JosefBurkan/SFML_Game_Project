#pragma once
#include <iostream>
#include "../../GridSystem/GridHandler/GridHandler.hpp"
#include "../../Maps/MapLayouts/Map/Map.hpp"
#include "../../Hitboxes/AttackManager/AttackManager.hpp"
#include "../../config.hpp"

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
            sf::Texture deathTexture;
            std::string spritePath;
            sf::Texture iconTexture;
            
            int tileSize = 50;
            int movement = 5;

            // For defaultsprite
            int spriteSizeY = 50;           // Størrelse på spritesheet
            int spriteSizeX = 100;
            int defaultDrawSpeed = 20;
            int defaultTextureY = 0;        // Lokasjonen til defaultsprite
            int defaultTextureX = 0;

            // For attacksprite
            int attackSpriteSizeY = 100;           // Størrelse på spritesheet
            int attackSpriteSizeX = 100;
            int attackingTextureY = 0;      // Lokasjonen til attacksprite
            int attackingTextureX = 0;
            int attackingDrawSpeed = 5;

            // For deathsprite
            int dyingTextureSizeX = 100;
            int dyingTextureSizeY = 100;
            int dyingTextureY = 0;
            int dyingTextureX = 0;

            // For levelUpEffekt
            


            bool resetAnimationsLock = false;
            int framesUntilDraw = 20;       // Hvor fort en animasjon skal tegnes
            int framesUntilAttackDraw = 20;
            int framesUntilDeathDraw = 15;
            int framesUntilLevelUpDraw = 10;
            

            std::string lastHitBy = "None";

            int experience = 0;
            int experienceToLevelUp = 5;
            int experienceToGrant = 5;

        public: 
            std::optional<sf::Sprite> sprite;
            std::optional<sf::Sprite> attackSprite;
            std::optional<sf::Sprite> deathSprite;    

            int currentHealth = 2;
            int attackLevel = 1;
            int maxHealth = currentHealth;
            int turn = 0;           // Hvor i lista starter uniten
            int currentOrder = 0;   // Hvor i lista er uniten hver runde
            int speed = 2;
            int level = 1;

            int attackTimer = 24;           // Hvor lenge angrepsanimasjonen til uniten varer
            int maxAttackTimer = 24;

            int deathAnimationTimer = 60;

            int attackSpawnTimer = 16;   // Når angrepet (hitboxen) skal lages
            int maxAttackSpawnTimer = 16;

            bool inMenu = false;          // Sjekk om menyen er åpen, eksisterer for å fortelle dette til andre klasser og brukes kun av player               

            std::string type = "unit";
            std::string name = "default";
            std::string state = "Neutral";  // Kun for player

            // spritePath er for å kunne sette sprites til enheter når de opprettes
            Unit(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks);
            void spawn();
            void Move(float posX, float posY);
            virtual sf::Sprite GetIcon();
            std::pair<int, int> RetrieveCoordinations();
            virtual void SetTileToOccupied();
            virtual void SetTileToUnOccupied();

            virtual void Draw(sf::RenderWindow& window);    // Default animasjon
            virtual void DrawUI(sf::RenderWindow& window);
            virtual void DrawAttackAnimation(sf::RenderWindow& window); // Når de angriper
            virtual void DrawDeathAnimation(sf::RenderWindow& window); 
            virtual void DrawLevelUpAnmiation (sf::RenderWindow& window);

            virtual void CheckForMapObjects();
            virtual bool IsHit();
            virtual void PerformActions(); // Bevegelse, angrep, osv.. Men kun for fiender
            virtual void Movement();    // Bevegelse for spiller. Skal slå den sammen med 'PerformActions' etterhvert
            virtual void ResetAnimations(); // Set animasjoner tilbake til starten, slik at de ikke kan starte midt i
            virtual void ResetAttackAnimation();
            virtual void ResetDeathAnimation();

            virtual void Attack(float spawnLocationX, float spawnLocationY);

            void RecieveExperience(int exp);
            int GrantExperience();
            int GetExperience();
            bool CheckForLevelUp();

            virtual void SaveData();    // Lagre, hente og sette data fra tidligere økter
            virtual void ReadData();
            virtual void SetData(std::array<int, 6> stats);

            std::string LastHitBy();
    };
}
