#pragma once
#include "../../../config.hpp" 

namespace Menus
{
    class Menu
    {
        protected:
            float menuPositionX = 0;
            float menuPositionY = 0;

            int arrowIndexX = 0;
            int arrowIndexY = 0;

            int lengthOfArray = 3;

            sf::Font font;

            std::array<std::string, 3> content;

            sf::ConvexShape arrow;

        public: 
            sf::RectangleShape optionsMenu;
            
            
            int index = 0;                   // Hvilket element i menyen man har valgt
            int movementCooldown = 15;
            int returnedIndex = 0;

            bool show = false;                  // Vis fram menyen

            Menu(std::array<std::string, 3> menutext);
            void SetPosition(float positionX, float positionY);
            void Draw(sf::RenderWindow& window);
            virtual std::array<sf::Text, 3> AddItems();
            int NavigateMenu();
    };

}
