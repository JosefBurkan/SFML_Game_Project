#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Game/Map_1/Map_1.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/UI/Game/StartMenu/StartMenu.hpp"

namespace Games
{

    class Game
    {   
        private:
        bool paused = false;
        bool previousEscapeState = false; // Omhandler knappen "escape"

        Maps1::Map1 map1;
        sf::RenderWindow newWindow; // vinduet som lages når spillet kjøres
        sf::RenderWindow window;    // vindet som skal brukes

        //Bruk forward declaration på dette:
        StartMenus::StartMenu menu;

        sf::View moveView;

        // Cameras::Camera camera;
            
        public:
            Game();
            void Pause();
            void LoadWindow();
            void Run();
    };
}
