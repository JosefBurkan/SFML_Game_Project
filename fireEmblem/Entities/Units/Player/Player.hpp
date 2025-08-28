#pragma once
#include "../../../config.hpp"
#include "../Unit.hpp"
#include "../../../GridSystem/GridHandler/GridHandler.hpp"
#include "../../../UI/Player/Menu/Menu.hpp"
#include "../../../Hitboxes/Attacks/Attack/Attack.hpp"


namespace GridGenerators 
{
    class GridGenerator;
}

namespace Players 
{
    class Player : public Units::Unit 
    {

        private:
            GridHandlers::GridHandler& GridHandler;          // Funksjonalitet for bevegelse
            Menus::Menu menu;

            int playerCurrentTileX = 0;
            int playerCurrentTileY = 0;
            int menuCooldown;                                   // Prevents spammable buttons
            bool isSelected = false;                            // Sjekk om spilleren har blitt valgt
            bool preventSelect = false;                         // Forebygg at spilleren kan velges
            sf::Vector2f realTimePos = sprite->getPosition();   // Hent spilleren sin posisjon
            int attackCooldown;

        public:
            std::string state = "Neutral";
            bool inMenu = false;                                // Sjekk om menyen er åpen, eksisterer for å fortelle dette til andre klasser
            Player(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler);
            bool IsPlayerStateReady();                          // Er spillertilstanden ledig?
            void Attack();                                      // Velg en rute innenfor rekkevidde, og angrip den
            void Movement();
            std::pair<int, int> TransformPositionToIndex(float spriteX, float spriteY);      // Oversett kordinater til rutenettet. feks. 50x = [5]
            void DrawUI(sf::RenderWindow& window);
            void Draw(sf::RenderWindow& window);

    };
}


