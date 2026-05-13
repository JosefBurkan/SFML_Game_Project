#include "Button/Button.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/config.hpp"

namespace StartMenus
{
    class StartMenu
    {
        private:

        Buttons::Button button1{"Resume", 0, 350, 100};
        Buttons::Button button2{"Options", 0, 350, 200};
        Buttons::Button button3{"Quit", 0, 350, 300};

        std::array<Buttons::Button, 3> menuButtons = {button1, button2, button3};

        int index = 1; // Hvilken knapp er valgt
        int menuCooldown = 20; // Ventetid så man ikke beveger menyen alt for fort


        public:
            StartMenu();
            std::string Action();
            void Run(sf::RenderWindow& window);

    };
}