#include "FireMage.hpp"

namespace FireMages
{
    FireMage::FireMage(GridGenerators::GridGenerator& gridReference, Maps::Map& map, 
                    AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler)
        : Player(gridReference, map, attacks, GridHandler)
    {
        name = "FireMage";
        playerCurrentTileY = 100;

        sprite->setTextureRect(sf::IntRect({0, 0}, {50, 50}));
    }
}

