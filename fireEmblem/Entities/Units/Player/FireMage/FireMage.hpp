#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Player/Player.hpp"


namespace FireMages
{
    class FireMage : public Players::Player 
    {
        public:
            FireMage(GridHandlers::GridHandler& gridHandler, Maps::Map& map, AttackManagers::AttackManager& attacks);

    };
}