#include "FireMage.hpp"

namespace FireMages
{
    FireMage::FireMage(GridHandlers::GridHandler& gridHandler,
                    AttackManagers::AttackManager& attacks)
        : Player(gridHandler, attacks)
    {

        name = "FireMage";

        auto& tiles = gridHandler.RetrieveAllTiles();

        tileLocation.y = 2;

        tiles[tileLocation.y][tileLocation.x].SetUnit(this);

        animations = &fireMageAnimations;

        animations->setPositions({100.f, 100.f});


    }
}

