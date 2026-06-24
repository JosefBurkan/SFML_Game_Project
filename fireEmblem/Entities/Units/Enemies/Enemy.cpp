#include "Enemy.hpp"
#include "../../../config.hpp"

namespace Enemies
{
    Enemy::Enemy(GridHandlers::GridHandler& gridHandler, AttackManagers::AttackManager& attacks, float yPos, float xPos)
        : Unit(gridHandler, attacks)
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Pixel_Bat.png")) 
        {
            throw std::runtime_error("Failed to load texture!");

        }

        name = "Bat";
        type = "Enemy";

        sprite.emplace(defaultTexture);
        sprite->setScale({3.f, 3.f});
        sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));
        sprite->setPosition({yPos, xPos});

        iconTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Slime/slime_Icon.png");

    }

    void Enemy::SetTileToOccupied()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();

        tiles[tileLocation.y][tileLocation.x].IsOccupied = true;
        tiles[tileLocation.y][tileLocation.x].SetUnit(this);
    }

    void Enemy::SetTileToUnOccupied()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();

        tiles[tileLocation.y][tileLocation.x].IsOccupied = false;
        tiles[tileLocation.y][tileLocation.x].RemoveUnit();

    }

    void Enemy::PerformActions()
    {
        
    }

}