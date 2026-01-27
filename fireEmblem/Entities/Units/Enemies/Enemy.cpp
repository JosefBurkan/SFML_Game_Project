#include "Enemy.hpp"

namespace Enemies
{
    Enemy::Enemy(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks, float yPos, float xPos)
        : Unit(gridReference, map, attacks)
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

        iconTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/slime_Icon.png");

    }

    void Enemy::Draw(sf::RenderWindow& window)
    {
        framesUntilDraw++;

        if (framesUntilDraw >= 12)
        {
            while (defaultTextureX >= 32)
            {
                defaultTextureY += 16;
                defaultTextureX = 0;

                if (defaultTextureY >= 24)
                {
                    defaultTextureY = 0;
                }
            }
            sprite->setTextureRect(sf::IntRect({defaultTextureX, defaultTextureY}, {16, 16}));

            defaultTextureX += 16;

            framesUntilDraw = 0;
        }
        window.draw(*sprite);
    }

    void Enemy::PerformActions()
    {
        
    }

    void Enemy::SetTileToOccupied()
    {
        auto& tiles = gridGenerator.RetrieveAllTiles();
        tiles[sprite->getPosition().y / 50][sprite->getPosition().x / 50].IsOccupied = true;
    }

    void Enemy::SetTileToUnOccupied()
    {
        auto& tiles = gridGenerator.RetrieveAllTiles();
        tiles[sprite->getPosition().y / 50][sprite->getPosition().x / 50].IsOccupied = false;
    }

}