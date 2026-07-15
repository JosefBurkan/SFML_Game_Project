#include "Swordsman.hpp"

namespace Swordsmen
{
    Swordsman::Swordsman(GridHandlers::GridHandler& gridHandler,
                    AttackManagers::AttackManager& attacks)
        : Player(gridHandler, attacks)
    {
        if (!iconTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Swordsman/Swordsman_Icon.png"))
        {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!iconTextureLarge.loadFromFile(std::string(ASSETS_DIR) + "Maps/Forest/ForestMushroom.png"))
        {
            throw std::runtime_error("Failed to load texture!");
        }

        auto& tiles = gridHandler.RetrieveAllTiles();

        tileLocation.y = 3;

        tiles[tileLocation.y][tileLocation.x].SetUnit(this);

        name = "Swordsman";
        maxHealth = currentHealth;

        attackTimer = 30;
        maxAttackTimer = attackTimer;

        attackSpawnTimer = 20;
        maxAttackSpawnTimer = attackSpawnTimer;

        speed = 1;

        animations = &swordsmanAnimations;
    }

    void Swordsman::Attack(sf::Vector2f position)
    {
        attacks.CreateAttack(name, attackLevel, position);
        attackSpawnTimer = maxAttackSpawnTimer;
    }
}

