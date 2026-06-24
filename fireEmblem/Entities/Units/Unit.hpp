#pragma once
#include "../../GridSystem/GridHandler/GridHandler.hpp"
#include "../../Hitboxes/AttackManager/AttackManager.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Effects/DamageNumbers/DamageNumbers.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/UI/Units/Health/HealthBar.hpp"
#include "../../config.hpp"

namespace Units 
{
    class Unit 
    {
        protected:  
            GridHandlers::GridHandler& gridHandler;
            AttackManagers::AttackManager& attacks;
            HealthBars::HealthBar healthBar;

            sf::Texture defaultTexture;
            sf::Texture attackTexture;      // Animasjon for når en karakter angriper
            sf::Texture deathTexture;
            sf::Texture movingTexture;       // Bevegelsesanimasjon
            std::string spritePath;
            sf::Texture iconTexture;
            DamageNumbers::DamageNumber damageNumber;

            sf::Vector2f tileLocation = {0, 0}; // Kordinater i index
            
            int tileSize = 50;
            int movement = 20;

            // For defaultsprite
            int spriteSizeY = 50;           // Størrelse på spritesheet
            int spriteSizeX = 100;
            int defaultTextureY = 0;        // Lokasjonen til defaultsprite
            int defaultTextureX = 0;
            int defaultDrawSpeed = 20;

            // For attacksprite
            int attackSpriteSizeY = 100;           // Størrelse på spritesheet
            int attackSpriteSizeX = 100;
            int attackingTextureY = 0;      // Lokasjonen til attacksprite
            int attackingTextureX = 0;
            int attackingDrawSpeed = 5;

            // For deathsprite
            int dyingSpriteSizeX = 100; // Størrelse på spritesheet
            int dyingSpriteSizeY = 100;
            int dyingTextureY = 0;
            int dyingTextureX = 0;

            // For bevegelsessprite
            int movingSpriteSizeY = 50;           // Størrelse på spritesheet
            int movingSpriteSizeX = 100;
            int movingTextureY = 0;      // Lokasjonen til attacksprite
            int movingTextureX = 0;
            int movingDrawSpeed = 5;
            


            bool resetAnimationsLock = false;
            int framesUntilDraw = 20;       // Hvor fort en animasjon skal tegnes
            int framesUntilAttackDraw = 20;
            int framesUntilDeathDraw = 15;
            int framesUntilMovementDraw = 15;
            int framesUntilLevelUpDraw = 10;
            

            std::string lastHitBy = "None";

            int experience = 0;
            int experienceToLevelUp = 5;
            int experienceToGrant = 5;

        public: 
            sf::Texture iconTextureLarge;
    
            std::optional<sf::Sprite> sprite;
            std::optional<sf::Sprite> attackSprite;
            std::optional<sf::Sprite> deathSprite;  
            std::optional<sf::Sprite> movingSprite;    

            int currentHealth = 2;
            int attackLevel = 1;
            int maxHealth = currentHealth;
            int turn = 0;           // Hvor i lista starter uniten
            int currentOrder = 0;   // Hvor i lista er uniten hver runde
            int speed = 2;
            int level = 1;
            bool finishedMoving = false;

            int attackTimer = 24;           // Hvor lenge angrepsanimasjonen til uniten varer
            int maxAttackTimer = 24;
            int numOfMoves = 0;     // For bevegelse. Brukes kun for fiender for øyeblikket
            int movementSpeed = 7;  // For bevegelsesanimasjonen sin hastighet
            int movementTime = 0;       // Hvor lenge skal bevegelsen vare

            bool playerDetected = false;    // For fiender

            int deathAnimationTimer = 60;

            int attackSpawnTimer = 16;   // Når angrepet (hitboxen) skal lages 
            int maxAttackSpawnTimer = 16;

            bool inMenu = false;          // Sjekk om menyen er åpen, eksisterer for å fortelle dette til andre klasser og brukes kun av player               

            std::string type = "unit";
            std::string name = "default";
            std::string state = "Neutral";  // Kun for player

            // spritePath er for å kunne sette sprites til enheter når de opprettes
            Unit(GridHandlers::GridHandler& gridHandler, AttackManagers::AttackManager& attacks);
            void setTileUnit();                 // Sette seg selv som peker for en spesifik tile
            void SetDamageNumber(std::string damageTaken); // For tallet som kommer over uniten når de blir skadet
            virtual sf::Sprite GetIcon();
            sf::Vector2f GetPosition();
            virtual void SetTileToOccupied();
            virtual void SetTileToUnOccupied();

            virtual void Draw(sf::RenderWindow& window);    // Default animasjon
            virtual void DrawUI(sf::RenderWindow& window);
            virtual void DrawAttackAnimation(sf::RenderWindow& window); // Når de angriper
            virtual void DrawDeathAnimation(sf::RenderWindow& window); 
            virtual void DrawMovingAnimation(sf::RenderWindow& window); // Når en enhet beveger seg
            virtual void DrawLevelUpAnmiation(sf::RenderWindow& window);
            void DrawDamageNumber(sf::RenderWindow& window);
            void DrawHealthBar(sf::RenderWindow& window);

            virtual bool IsHit();
            virtual void PerformActions(); // Bevegelse, angrep, osv.. Men kun for fiender
            virtual void CheckForMapObjects();
            virtual void Place(float posX, float posY);
            virtual void Movement();    // Bevegelse for spiller. Skal slå den sammen med 'PerformActions' etterhvert
            virtual void SmoothMove();
            virtual void ResetAnimations(); // Set animasjoner tilbake til starten, slik at de ikke kan starte midt i
            virtual void ResetAttackAnimation();
            virtual void ResetDeathAnimation();
            virtual void SetPathToPlayer();             // Kjør algorithmen som scanner etter spiller og lager vei (For fiender)
            virtual void MenuActions();
            void ReverseSprite(int movementX, int movementY);               // Snu spriten rundt (Hovedsakelig hjelpsom for løping)

            virtual void Attack(sf::Vector2f position);

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
