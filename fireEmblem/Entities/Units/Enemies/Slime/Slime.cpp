#include "Slime.hpp"

namespace Slimes
{
    Slime::Slime(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks, float yPos, float xPos)
        : Enemy(gridReference, map, attacks, yPos, xPos)
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Slime-2.png")) 
        {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!deathTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Slime_Death_Animation.png")) 
        {
            throw std::runtime_error("Failed to load texture!");
        }

        name = "Slime";

        sprite.emplace(defaultTexture);
        sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));
        sprite->setScale({3.f, 3.f});
        sprite->setPosition({yPos, xPos});

        deathSprite.emplace(deathTexture);
        deathSprite->setTextureRect(sf::IntRect({0, 0}, {50, 50}));
        deathSprite->setPosition({yPos, xPos});


        movement = 4;

        iconTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/slime_Icon.png");
    }

    void Slime::Draw(sf::RenderWindow& window)
    {
        framesUntilDraw++;

        if (framesUntilDraw >= 8)
        {
            while (defaultTextureX >= 48)
            {
                defaultTextureY += 16;
                defaultTextureX = 0;

                if (defaultTextureY >= 48)
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

    // Håndterer bevegelse og angrep
    void Slime::PerformActions()
    {
        auto& tiles = gridGenerator.RetrieveAllTiles();
        playerPos = algorithm.CheckAvailableTiles(sprite->getPosition().y / 50, sprite->getPosition().x / 50, movement, tiles);

        // Hopp til spilleren dersom den er innen rekkevidde
        if (algorithm.playerDetected == true)
        {
            sprite->setPosition({(playerPos.second * 50) + 50, playerPos.first * 50});

            deathSprite->setPosition({sprite->getPosition().x, sprite->getPosition().y});

            float x = playerPos.second * 50;
            float y = playerPos.first * 50;

            attacks.CreateAttack(x, y);
        }

    }




}