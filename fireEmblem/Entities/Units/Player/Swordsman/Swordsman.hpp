#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/config.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Player/Player.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/GridHandler/GridHandler.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/UI/Player/Menu/Menu.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Hitboxes/Attacks/Attack/Attack.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/Algorithms/GridPathAlgorithm/GridPathAlgorithm.hpp"

namespace Swordsmen 
{
    class Swordsman : public Players::Player 
    {

        public:
            Swordsman(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler);

    };
}