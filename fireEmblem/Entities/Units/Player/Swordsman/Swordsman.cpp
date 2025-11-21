#include "Swordsman.hpp"

namespace Swordsmen
{
    Swordsman::Swordsman(GridGenerators::GridGenerator& gridReference, Maps::Map& map, 
                    AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler)
        : Player(gridReference, map, attacks, GridHandler)
    {
        if (!texture.loadFromFile(std::string(ASSETS_DIR) + "Swordsman.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        name = "Swordsman";
        healthPoints = 4;
        maxHealth = healthPoints;
        texture.setSmooth(false);

        type = "Player";
        speed = 3;

        sprite->setScale({1, 1});
        sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));
    }
}

