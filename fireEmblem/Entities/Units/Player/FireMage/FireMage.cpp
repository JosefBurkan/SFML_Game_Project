#include "FireMage.hpp"

namespace FireMages
{
    FireMage::FireMage(GridHandlers::GridHandler& gridHandler, Maps::Map& map, 
                    AttackManagers::AttackManager& attacks)
        : Player(gridHandler, map, attacks)
    {
        name = "FireMage";

        

        auto& tiles = gridHandler.RetrieveAllTiles();

        tileLocation.y = 2;

        tiles[tileLocation.y][tileLocation.x].SetUnit(this);

        sprite->setTextureRect(sf::IntRect({0, 0}, {50, 50}));
    }
}

