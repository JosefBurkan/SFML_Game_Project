#include "Menu.hpp"

namespace Menus
{
    Menu::Menu(std::array<std::string, 3> menutext)
        :   font(std::string(ASSETS_DIR) + "ARCADECLASSIC.TTF"),
            attack(font),
            skills(font),
            items(font),
            menuContents{&attack, &skills, &items}
    {
        arrow.setPointCount(3);
        arrow.setPoint(0, sf::Vector2f(0.1, 0.1));
        arrow.setPoint(1, sf::Vector2f(0.1, 0.9));
        arrow.setPoint(2, sf::Vector2f(0.9, 0.5));
        arrow.setScale({30.f, 30.f});

        optionsMenu.setSize({100, 200});
        optionsMenu.setFillColor({100, 200, 150, 180});
        optionsMenu.setOutlineColor({0, 0, 0, 255});
        optionsMenu.setOutlineThickness(3.f);

        content = menutext;
        

        // Sett menuContents sitt innhold til riktige verdier, utenom posisjon
        for (int i = 0; i < menuContents.size(); i++)
        {
            menuContents[i]->setString(content[i]);
            menuContents[i]->setCharacterSize(20);
        }

    }

    void Menu::SetPosition(float positionX, float positionY)
    {
        menuPositionX = positionX;
        menuPositionY = positionY;

        optionsMenu.setPosition({positionX, positionY});
        arrow.setPosition({menuPositionX - 35, menuPositionY + (index * 30 - 20)});
    }

    // For å vise hvor i menyen som brukeren er
    int Menu::NavigateMenu()
    {
        movementCooldown--;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && movementCooldown <= 0)
        {
            index++;
            movementCooldown = 10;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && movementCooldown <= 0)
        {
            index--;
            movementCooldown = 10;
        }
        if (index < 0)
        {
            index = 0;
        }
        else if (index > 2)
        {
            index = 2;
        }

        arrow.setPosition({menuPositionX - 35, menuPositionY + (index * 30)});
        
        return index;
    }

    // Legg til inholdet fra "menuStrings" inn i menyboksen
    std::array<sf::Text*, 3> Menu::AddItems()
    {
        float menyPosX = optionsMenu.getPosition().x;
        float menyPosY = optionsMenu.getPosition().y;

        returnedIndex = NavigateMenu();

        for (int i = 0; i < menuContents.size(); i++)
        {
            menuContents[i]->setPosition({menyPosX, menyPosY + (i * 30)});
            menuContents[i]->setFillColor(sf::Color::Red);
        }

        menuContents[returnedIndex]->setFillColor({255, 255, 100});

        return menuContents; 
        
    }

    void Menu::Draw(sf::RenderWindow& window) 
    {
        if (show)
        {
            auto menu = AddItems();

            window.draw(optionsMenu);
            window.draw(arrow);

            for (int i = 0; i < 3; i++)
            {
                window.draw(*menu[i]);
            }
        }
    }
}