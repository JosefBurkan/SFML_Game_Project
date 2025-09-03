#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Unit.hpp"


namespace Maps {
    class Map;
}

namespace Slimes
{
    class Slime : public Units::Unit
    {
        public:
            Slime(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks);
            void CheckForAttacks();
    };



}