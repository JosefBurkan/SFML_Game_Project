#include "Enemy.hpp"

namespace Enemies
{
    Enemy::Enemy(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks, float yPos, float xPos)
        : Unit(gridReference, map, attacks)
    {
        if (!texture.loadFromFile(std::string(ASSETS_DIR) + "Pixel-Bat.png")) 
        {
            throw std::runtime_error("Failed to load texture!");

        }

        name = "Bat";
        type = "Enemy";

        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});
        sprite->setPosition({yPos, xPos});

    }

    void Enemy::PerformActions()
    {
        
    }

}