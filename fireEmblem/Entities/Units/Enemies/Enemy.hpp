#pragma once
#include "../Unit.hpp"
#include "../../../Hitboxes/Attack/Attack.hpp"

namespace Maps {
    class Map;
}

namespace Enemies 
{
    class Enemy : public Units::Unit 
    {
        protected:

        public:
            Enemy(GridHandlers::GridHandler& gridHandler, Maps::Map& map, AttackManagers::AttackManager& attacks, float yPos, float xPos);
            void CheckForAttacks();
            void SetTileToOccupied() override;
            void SetTileToUnOccupied() override;
            void PerformActions() override;
            
        };
}
