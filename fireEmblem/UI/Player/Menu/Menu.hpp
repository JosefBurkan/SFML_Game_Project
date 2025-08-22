#pragma once
#include "../../../config.hpp"

namespace Menus
{
    class Menu
    {
        public: 
            sf::RectangleShape optionsMenu;
            std::vector<std::string> menuContents;
            
            int menuContentsIndex = 0;                   // Hvilket element i menyen man har valgt
            int movementCooldown = 30;
            int returnedIndex;

            bool show = false;                  // Vis fram menyen

            Menu();

            void SetPosition(float positionX, float positionY);
            void Draw(sf::RenderWindow& window);
            void AddItems(sf::RenderWindow& window);
            int NavigateMenu();
    };

}
