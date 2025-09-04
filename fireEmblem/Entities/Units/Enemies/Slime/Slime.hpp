#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Unit.hpp"


namespace Maps {
    class Map;
}

namespace Slimes
{
    class Slime : public Units::Unit
    {
        private:
            int framesUntilDraw = 0;
            int textureLocationY = 0;
            int textureLocationX = 0;
        public:
            Slime(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks);
            void CheckForAttacks();
            void Draw(sf::RenderWindow& window) override;
    };



}