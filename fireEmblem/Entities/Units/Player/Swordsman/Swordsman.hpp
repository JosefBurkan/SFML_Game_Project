#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Player/Player.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Sprites/SwordsmanSprite/SwordsmanSprite.hpp"


namespace Swordsmen 
{
    class Swordsman : public Players::Player 
    {
        public:
            SwordsmanSprites::SwordsmanSprite swordsmanAnimations;
            Swordsman(GridHandlers::GridHandler& gridHandler, AttackManagers::AttackManager& attacks);
            void Attack(sf::Vector2f position) override;

    };
}