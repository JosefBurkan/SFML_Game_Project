#pragma once
#include "../../../config.hpp"
#include "../Unit.hpp"
#include "../../../Hitboxes/Attacks/Attack/Attack.hpp"

namespace Maps {
    class Map;
}

namespace Enemies 
{
    class Enemy : public Units::Unit 
    {
        private:


        public:
            Enemy(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks, float yPos, float xPos);
            void CheckForAttacks();
            void Draw(sf::RenderWindow& window) override;
            void PerformActions() override;
            void SetTileToOccupied() override;
            void SetTileToUnOccupied() override;

    };
}
