#include "Enemy.hpp"

namespace Enemies
{
    Enemy::Enemy(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks, float yPos, float xPos)
        : Unit(gridReference, map, attacks)
    {
        if (!texture.loadFromFile(std::string(ASSETS_DIR) + "Pixel_Bat.png")) 
        {
            throw std::runtime_error("Failed to load texture!");

        }

        name = "Bat";
        type = "Enemy";

        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});
        sprite->setTextureRect(sf::IntRect({0, 0}, {16, 12}));
        sprite->setPosition({yPos, xPos});

    }

    void Enemy::Draw(sf::RenderWindow& window)
    {
        framesUntilDraw++;

        if (framesUntilDraw >= 10)
        {
            while (textureLocationX >= 32)
            {
                textureLocationY += 12;
                textureLocationX = 0;

                if (textureLocationY >= 24)
                {
                    textureLocationY = 0;
                }
            }
            sprite->setTextureRect(sf::IntRect({textureLocationX, textureLocationY}, {16, 12}));

            textureLocationX += 16;

            framesUntilDraw = 0;
        }
        window.draw(*sprite);
    }

    void Enemy::PerformActions()
    {
        
    }

}