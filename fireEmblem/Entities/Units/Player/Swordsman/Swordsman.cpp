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
        maxHealth = currentHealth;
        tileLocation.y = 150;

        sprite->setTextureRect(sf::IntRect({0, 0}, {50, 50}));

        if (!iconTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Swordsman/Swordsman_Icon.png"))
        {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!attackTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Swordsman/Swordsman_Slash.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        attackingDrawSpeed = 5;
        attackTimer = 30;
        maxAttackTimer = attackTimer;

        attackSpawnTimer = 20;
        maxAttackSpawnTimer = attackSpawnTimer;
    }

    void Swordsman::Attack(sf::Vector2f position)
    {
        attacks.CreateAttack(name, attackLevel, position);
        attackSpawnTimer = maxAttackSpawnTimer;
    }
}

