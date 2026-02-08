#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Player/Player.hpp"


namespace Swordsmen 
{
    class Swordsman : public Players::Player 
    {
        public:
            Swordsman(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler);
            void Attack(float spawnLocationX, float spawnLocationY) override;

    };
}