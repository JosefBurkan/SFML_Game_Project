#include "Enemy.hpp"
#include "../../../config.hpp"

namespace Enemies
{
    Enemy::Enemy(GridHandlers::GridHandler& gridHandler, AttackManagers::AttackManager& attacks, float yPos, float xPos)
        : Unit(gridHandler, attacks)
    {

        name = "Bat";
        type = "Enemy";

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