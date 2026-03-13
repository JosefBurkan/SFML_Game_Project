#include "Menu.hpp"

namespace Menus
{
    Menu::Menu(std::array<std::string, 3> menutext)
    {
        optionsMenu.setSize({100, 200});
        optionsMenu.setFillColor({100, 200, 150, 180});
        optionsMenu.setOutlineColor({0, 0, 0, 255});
        optionsMenu.setOutlineThickness(3.f);

        arrow.setFillColor({255, 255, 255});
        arrow.setSize({20, 20});

    }

    void Menu::SetPosition(float positionX, float positionY)
    {
        menuPositionX = positionX;
        menuPositionY = positionY;

        optionsMenu.setPosition({positionX, positionY});
        arrow.setPosition({menuPositionX - 30, menuPositionY + (index * 30 + 3)});
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

        arrow.setPosition({menuPositionX - 30, menuPositionY + (index * 30 + 3)});
        
        return index;
    }

    // Legg til inholdet fra "menuStrings" inn i menyboksen
    std::array<sf::Text, 3> Menu::AddItems()
    {

        float menyPosX = optionsMenu.getPosition().x;
        float menyPosY = optionsMenu.getPosition().y;

        font.openFromFile(std::string(ASSETS_DIR) + "ARCADECLASSIC.TTF");
        font.setSmooth(false); 
        
        sf::Text attack(font);
        sf::Text skills(font);
        sf::Text items(font);

        std::array<sf::Text, 3> menuContents = {attack, skills, items};

        menuContents[0] = attack;
        menuContents[1] = skills;
        menuContents[2] = items;

        menuContents[0].setString("Attack");
        menuContents[1].setString("Skills");
        menuContents[2].setString("Items");

        menuContents[0].setPosition({menyPosX, menyPosY + 10});
        menuContents[1].setPosition({menyPosX, menyPosY + 20});
        menuContents[2].setPosition({menyPosX, menyPosY + 30});

        returnedIndex = NavigateMenu();

        for (int i = 0; i < lengthOfArray; i++)
        {
            menuContents[i].setCharacterSize(20);
            menuContents[i].setFillColor(sf::Color::Red);

            menuContents[i].setPosition({menyPosX + 3, menyPosY + (i * 30) + 3});
        }

        menuContents[returnedIndex].setFillColor({255, 255, 100});

        return menuContents; 
        
    }

    void Menu::Draw(sf::RenderWindow& window) 
    {
        auto menu = AddItems();

        if (show)
        {
            window.draw(optionsMenu);
            window.draw(arrow);

            for (int i = 0; i < 3; i++)
            {
                window.draw(menu[i]);
            }
        }
    }
}