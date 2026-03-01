#include "FireMage.hpp"

namespace FireMages
{
    FireMage::FireMage(GridGenerators::GridGenerator& gridReference, Maps::Map& map, 
                    AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler)
        : Player(gridReference, map, attacks, GridHandler)
    {
        name = "FireMage";
        healthPoints = 3;
        maxHealth = healthPoints;
        playerCurrentTileY = 100;

        type = "Player";
        speed = 4;

        sprite->setTextureRect(sf::IntRect({0, 0}, {50, 50}));
    }
}

