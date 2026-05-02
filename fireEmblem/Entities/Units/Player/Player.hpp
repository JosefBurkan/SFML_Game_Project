#pragma once
#include "../Unit.hpp"
#include "../../../Hitboxes/Attack/Attack.hpp"
#include "../../../Hitboxes/Attack/RangedAttack/RangedAttack.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/Algorithms/GridPathAlgorithm/GridPathAlgorithm.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/UI/Player/Menu/Menu.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/UI/Player/Menu/Skills/Skills.hpp"


namespace Players 
{
    class Player : public Units::Unit 
    {
        protected:
            GridHandlers::GridHandler& GridHandler;          // Funksjonalitet for bevegelse
            GridPathAlgorithms::GridPathAlgorithm algorithm;

            std::array<std::string, 3> menutext = {"Attack", "Skills", "Items"};
            std::array<std::string, 3> skillsMenu = {"team boost", "Pow", "Love"};
            Menus::Menu menu{menutext};
            Skillss::Skills skills{skillsMenu};

            float playerCurrentTileY = 100;
            float playerCurrentTileX = 0;
            int menuCooldown = 30;                              // Gjør at det enklere å bruke menyen
            bool isSelected = false;                            // Sjekk om spilleren har blitt valgt
            bool preventSelect = false;                         // Forebygg at spilleren kan velges
            std::pair<float, float> selectedTile;               // Ruten som spilleren står spilleren på
            std::pair<float, float> retrievedTile;              // Ruten som for øyeblikket er valgt
            sf::Vector2f previousPosition = sprite->getPosition();   // Hent spilleren sin posisjon
            std::pair<int, int> previousTilePosition = {0, 0};   // Hent spilleren sin posisjon


        public:
            Player(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler);
            void Movement() override;
            std::pair<int, int> TransformPositionToIndex(float spriteX, float spriteY);      // Oversett kordinater til rutenettet. feks. 50x = [5]
            void DrawUI(sf::RenderWindow& window) override;
            // void Draw(sf::RenderWindow& window) override;
            void SetTileToOccupied() override;
            void SetTileToUnOccupied() override;            
            void CancelSelect();
            void Attack(float spawnLocationX, float spawnLocationY) override;
            void ConfirmMovement();
            bool IsMenuOpen();

    };
}


