#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/config.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Unit.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Player/Player.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Player/Swordsman/Swordsman.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Enemies/Enemy.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Enemies/Slime/Slime.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/GridHandler/GridHandler.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Camera/Camera.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Maps/MapLayouts/StartMap/StartMap.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Maps/Background/Background1/Background1.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Managers/UnitManager/UnitManager.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Hitboxes/Attacks/AttackManager/AttackManager.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/UI/Player/Menu/Menu.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/UI/Units/OverView/OverView.hpp"

namespace Games
{
    class Game
    {
    private:
        StartMaps::StartMap map;
        GridGenerators::GridGenerator& grid;
        GridHandlers::GridHandler gridHandler;
        Backgrounds1::Background1 background1;

        OverViews::OverView overView;
        AttackManagers::AttackManager attacks;
        UnitsManagers::UnitsManager unitManager;
        Cameras::Camera camera;

        std::shared_ptr<Players::Player> you;
        std::shared_ptr<Enemies::Enemy> enemy1;
        std::shared_ptr<Slimes::Slime> enemy2;
        std::shared_ptr<Slimes::Slime> slime2;
        std::shared_ptr<Swordsmen::Swordsman> swordsman;

        sf::RectangleShape shader;
        
        int gameTurn = 0;
        int cooldown = 0; // Ventetid mellom enheter sine handlinger
        int numberOfUnits = 5; // Antall enheter i unitmanager
        bool lock = false;  // Brukes for å utføre funksjoner en gang, istedenfor at de repeteres mange ganger
        
        
    public:
        Game();
        void Run();
    };
}
