#include "Swordsman.hpp"

namespace Swordsmen
{
    Swordsman::Swordsman(GridHandlers::GridHandler& gridHandler, Maps::Map& map, 
                    AttackManagers::AttackManager& attacks)
        : Player(gridHandler, map, attacks)
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Swordsman/Swordsman.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!iconTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Swordsman/Swordsman_Icon.png"))
        {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!iconTextureLarge.loadFromFile(std::string(ASSETS_DIR) + "Maps/Forest/ForestMushroom.png"))
        {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!attackTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Swordsman/Swordsman_Slash.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!movingTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Swordsman/Swordsman_Running.png")) {
            throw std::runtime_error("Failed to load texture!");
        }


        auto& tiles = gridHandler.RetrieveAllTiles();

        tileLocation.y = 3;

        tiles[tileLocation.y][tileLocation.x].SetUnit(this);

        movingSprite->setPosition(tileLocation * 50.f);

        sprite->setTextureRect(sf::IntRect({0, 0}, {50, 50}));

        
        name = "Swordsman";
        maxHealth = currentHealth;

        attackingDrawSpeed = 5;
        attackTimer = 30;
        maxAttackTimer = attackTimer;

        attackSpawnTimer = 20;
        maxAttackSpawnTimer = attackSpawnTimer;

        speed = 1;
    }

    void Swordsman::Attack(sf::Vector2f position)
    {
        attacks.CreateAttack(name, attackLevel, position);
        attackSpawnTimer = maxAttackSpawnTimer;
    }
}

