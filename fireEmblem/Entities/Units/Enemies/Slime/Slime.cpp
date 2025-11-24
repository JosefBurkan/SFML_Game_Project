#include "Slime.hpp"

namespace Slimes
{
    Slime::Slime(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks, float yPos, float xPos)
        : Enemy(gridReference, map, attacks, yPos, xPos)
    {
        if (!texture.loadFromFile(std::string(ASSETS_DIR) + "Slime-2.png")) 
        {
            throw std::runtime_error("Failed to load texture!");

        }

        name = "Slime";

        sprite.emplace(texture);
        sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));
        sprite->setScale({3.f, 3.f});
        sprite->setPosition({yPos, xPos});
        movement = 4;

        iconTexture.loadFromFile(std::string(ASSETS_DIR) + "slime_Icon.png");
    }

    void Slime::Draw(sf::RenderWindow& window)
    {
        framesUntilDraw++;

        if (framesUntilDraw >= 8)
        {
            while (textureLocationX >= 48)
            {
                textureLocationY += 16;
                textureLocationX = 0;

                if (textureLocationY >= 48)
                {
                    textureLocationY = 0;
                }
            }
            sprite->setTextureRect(sf::IntRect({textureLocationX, textureLocationY}, {16, 16}));

            textureLocationX += 16;

            framesUntilDraw = 0;
        }
        window.draw(*sprite);
    }

    // Håndterer bevegelse og angrep
    void Slime::PerformActions()
    {
        auto& tiles = gridGenerator.RetrieveAllTiles();
        playerPos = algorithm.CheckAvailableTiles(sprite->getPosition().y / 50, sprite->getPosition().x / 50, movement, tiles);

        // Hopp til spilleren dersom den er innen rekkevidde
        if (algorithm.playerDetected == true)
        {
            sprite->setPosition({(playerPos.second * 50) + 50, playerPos.first * 50});
            Attacks::Attack newAttack{playerPos.second * 50, playerPos.first * 50};
            attacks.CreateAttack(newAttack);
        }

    }




}