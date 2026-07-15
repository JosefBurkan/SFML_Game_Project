#pragma once
#include "../Unit.hpp"
#include "../../../Hitboxes/Attack/Attack.hpp"
#include "../../../Hitboxes/Attack/RangedAttack/RangedAttack.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/Algorithms/GridPathAlgorithm/GridPathAlgorithm.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/Algorithms/PlayerPathAlgorithm/PlayerPathAlgorithm.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/UI/Player/Menu/Menu.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/UI/Player/Menu/Skills/Skills.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Sprites/FireMageSprite/FireMageSprite.hpp"


namespace Players 
{
    class Player : public Units::Unit 
    {
        protected:
            GridPathAlgorithms::GridPathAlgorithm algorithm;
            PlayerPathAlgorithms::PlayerPathAlgorithm pathAlgorithm;

            std::array<std::string, 3> menutext = {"Attack", "Skills", "Items"};
            std::array<std::string, 3> skillsMenu = {"team boost", "Pow", "Love"};
            Menus::Menu menu{menutext};
            Skillss::Skills skills{skillsMenu};

            int moving = 0;                                    // Hvor lenge animasjonen for å bevege seg skal vare

            sf::Vector2f gridCurrentTile = {0, 0};

            int menuCooldown = 30;                              // Gjør at det enklere å bruke menyen
            bool isSelected = false;                            // Sjekk om spilleren har blitt valgt
            bool preventSelect = false;                         // Forebygg at spilleren kan velges
            Tiles::Tile selectedTile;                           // Ruten som spilleren står spilleren på
            std::pair<float, float> retrievedTile;              // Ruten som for øyeblikket er valgt
            sf::Vector2f previousPosition = {0, 0};   // Hent spilleren sin posisjon
            std::vector<Tiles::Tile> path = {};


        public:
            Player(GridHandlers::GridHandler& gridHandler, AttackManagers::AttackManager& attacks);
            void Movement() override;
            void SmoothMove() override;
            void SetPathToSelectedTile();
            void DrawUI(sf::RenderWindow& window) override;
            // void Draw(sf::RenderWindow& window) override;
            void SetTileToOccupied() override;
            void RevertOccupation();     // Sett okkupasjonen til sånn den var før spilleren bevegde seg      
            void CancelSelect();
            void Attack(sf::Vector2f position) override;
            void ConfirmMovement();
            bool IsMenuOpen();
            
            void MenuActions() override;

            void SaveData() override;    // Lagre og hente data fra tidligere økter
            void ReadData() override;
            void SetData(std::array<int, 6> stats) override;

    };
}


