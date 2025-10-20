#pragma once

#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Unit.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Player/Player.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Enemies/Enemy.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Enemies/Slime/Slime.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/GridHandler/GridHandler.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Camera/Camera.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Maps/MapLayouts/StartMap/StartMap.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Maps/Background/Background1/Background1.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Managers/UnitManager/UnitManager.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Hitboxes/Attacks/AttackManager/AttackManager.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/UI/Player/Menu/Menu.hpp"

namespace Games
{
    class Game
    {
    private:
        StartMaps::StartMap map;
        AttackManagers::AttackManager attacks;
        UnitsManagers::UnitsManager unitManager;

        // Gjør disse til pointers slik at de kan brukes utenfor konstruktøren
        std::unique_ptr<GridHandlers::GridHandler> gridHandler;
        std::unique_ptr<Cameras::Camera> camera;
        std::unique_ptr<Backgrounds1::Background1> background1;

        std::shared_ptr<Players::Player> you;
        std::shared_ptr<Enemies::Enemy> enemy1;
        std::shared_ptr<Slimes::Slime> enemy2;

        sf::RectangleShape shader;
        sf::Clock clock;

        
        int turn = 0;
        int cooldown = 0; // Ventetid mellom enheter sine handlinger
        
    public:
        Game();
        void Run();
    };
}
