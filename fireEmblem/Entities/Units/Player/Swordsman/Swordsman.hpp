#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Player/Player.hpp"


namespace Swordsmen 
{
    class Swordsman : public Players::Player 
    {
        public:
            Swordsman(GridHandlers::GridHandler& gridHandler, AttackManagers::AttackManager& attacks);
            void Attack(sf::Vector2f position) override;

    };
}