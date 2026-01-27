#include "Swordsman.hpp"

namespace Swordsmen
{
    Swordsman::Swordsman(GridGenerators::GridGenerator& gridReference, Maps::Map& map, 
                    AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler)
        : Player(gridReference, map, attacks, GridHandler)
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Swordsman/Swordsman.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        name = "Swordsman";
        healthPoints = 4;
        maxHealth = healthPoints;
        playerCurrentTileY = 150;

        type = "Player";
        speed = 1;

        sprite->setScale({1, 1});
        sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));

        if (!iconTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Swordsman/Swordsman_Icon.png"))
        {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!attackTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Swordsman/Swordsman_Slash.png")) {
            throw std::runtime_error("Failed to load texture!");
        }
    }
}

