#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Player/Player.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Sprites/FireMageSprite/FireMageSprite.hpp"

namespace FireMages
{
    class FireMage : public Players::Player 
    {

        public:
            FireMageSprites::FireMageSprite fireMageAnimations;
            FireMage(GridHandlers::GridHandler& gridHandler, AttackManagers::AttackManager& attacks);
    };
}