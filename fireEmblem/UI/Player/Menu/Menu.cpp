#include "Menu.hpp"

namespace Menus
{

    Menu::Menu()
    {
        optionsMenu.setSize({100, 200});
        optionsMenu.setFillColor({100, 200, 150, 180});
        optionsMenu.setOutlineColor({0, 0, 0, 255});
        optionsMenu.setOutlineThickness(3.f);

        arrow.setFillColor({255, 255, 255});
        arrow.setSize({20, 20});

        menuContents.push_back("Attack");
        menuContents.push_back("Skills");
        menuContents.push_back("Items");
    }

    void Menu::SetPosition(float positionX, float positionY)
    {
        optionsMenu.setPosition({positionX, positionY});
        arrow.setPosition({positionX - 30, positionY + 6});


    }

    // For å vise hvor i menyen som brukeren er
    int Menu::NavigateMenu()
    {
        movementCooldown++;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && movementCooldown >= 30)
        {
            menuContentsIndex++;
            movementCooldown = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && movementCooldown >= 30)
        {
            menuContentsIndex--;
            movementCooldown = 0;
        }
        if (menuContentsIndex < 0)
        {
            menuContentsIndex = 0;
        }
        else if (menuContentsIndex > 2)
        {
            menuContentsIndex = 2;
        }

        return menuContentsIndex;
    }

    // Legg til inholdet i "menuContents" inn i menyboksen
    void Menu::AddItems(sf::RenderWindow& window) 
    {
        sf::Font font(std::string(ASSETS_DIR) + "ARCADECLASSIC.TTF");
        font.setSmooth(false); 

        for (int itemIndex = 0; itemIndex < menuContents.size(); itemIndex++)
        {
            returnedIndex = NavigateMenu();
            sf::Text text(font);

            text.setString(menuContents[itemIndex]);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Red);

            if (returnedIndex == itemIndex)
            {
                text.setFillColor({255, 255, 100});
            }

            text.setPosition({optionsMenu.getPosition().x + 3, optionsMenu.getPosition().y + itemIndex * 30 + 3});
            window.draw(text);
        }
    }

    void Menu::Draw(sf::RenderWindow& window) 
    {
        if (show == true)
        {
            window.draw(optionsMenu);
            window.draw(arrow);
            AddItems(window);
        }
    }
}