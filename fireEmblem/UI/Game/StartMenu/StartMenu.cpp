#include "StartMenu.hpp"

namespace StartMenus
{
    StartMenu::StartMenu()
    {

    }

    std::string StartMenu::Action()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
        {
            switch (index)
            {
                case 0:
                    return "Resume";

                case 1:
                    return "Options";

                case 2:
                    return "Quit";
            }
        }
        return "Nothing";
    }

    void StartMenu::Run(sf::RenderWindow& window)
    {
        if (menuCooldown <= 0)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && index > 0)
            {
                index--;
                menuCooldown = 10;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && index < menuButtons.size() - 1)
            {
                index++;
                menuCooldown = 10;
            }
        }

        if (menuCooldown > 0)
        {
            menuCooldown--;
        }

        for (int i = 0; i < menuButtons.size(); i++)
        {
            if (i == index)
            {
                menuButtons[i].Select();
            }
            else
            {
                menuButtons[i].DeSelect();
            }

            menuButtons[i].Draw(window);
        }
    }


}