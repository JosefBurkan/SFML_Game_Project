#include "Slime.hpp"

namespace Slimes
{
    Slime::Slime(GridHandlers::GridHandler& gridHandler, Maps::Map& map, AttackManagers::AttackManager& attacks, float yPos, float xPos)
        : Enemy(gridHandler, map, attacks, yPos, xPos)
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Slime/Slime-2.png")) 
        {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!deathTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Slime/Slime_Death_Animation.png")) 
        {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!iconTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Slime/Slime_Icon.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!iconTextureLarge.loadFromFile(std::string(ASSETS_DIR) + "Units/Slime/Slime_Icon_Zoom.png"))
        {
            throw ("File not found ");
        }


        name = "Slime";

        auto& tiles = gridHandler.RetrieveAllTiles();

        // Må reverseres her
        tileLocation.x = yPos / 50;
        tileLocation.y = xPos / 50;

        std::cout << "\nY Koordinat:" << tileLocation.y;

        tiles[tileLocation.y][tileLocation.x].SetUnit(this);
        tiles[tileLocation.y][tileLocation.x].IsOccupied = true;

        // std::cout << "\nTest: " << tiles[tileLocation.y][tileLocation.x].unit->name;

        std::cout << "Stored ptr: " << tiles[tileLocation.y][tileLocation.x].unit << '\n';

        sprite.emplace(defaultTexture);
        sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));
        sprite->setScale({3.f, 3.f});
        sprite->setPosition({yPos, xPos});

        deathSprite.emplace(deathTexture);
        deathSprite->setTextureRect(sf::IntRect({0, 0}, {50, 50}));
        deathSprite->setPosition({yPos, xPos});

        movement = 4;

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
        if (!pathToPlayer.empty())
        {
            attacks.CreateAttack(name, attackLevel, pathToPlayer[0].GetPosition());
        }
    }

    void Slime::Movement()
    {
        if (!pathToPlayer.empty())
        {
            if (cooldown == 0)
            {

                auto& tiles = gridHandler.RetrieveAllTiles();

                float currentTileY = pathToPlayer[numOfMoves].GetPosition().y;
                float currentTileX = pathToPlayer[numOfMoves].GetPosition().x;

                if (numOfMoves > 1)
                {
                    numOfMoves--;
                }

                nextTileY = pathToPlayer[numOfMoves].GetPosition().y;
                nextTileX = pathToPlayer[numOfMoves].GetPosition().x;


                calculatedPathX = (nextTileX - currentTileX) / 10;
                calculatedPathY = (nextTileY - currentTileY) / 10;

                cooldown = 10;
            }

            cooldown--;

            if (algorithm.playerDetected == true)
            {
                sprite->move({calculatedPathX, calculatedPathY});
                deathSprite->setPosition({sprite->getPosition().x, sprite->getPosition().y});
            }
        }
    }

    void Slime::SetPathToPlayer()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();

        pathToPlayer = algorithm.CheckAvailableTiles(sprite->getPosition().y / 50, sprite->getPosition().x / 50, movement, tiles);

        numOfMoves = pathToPlayer.size() - 1;

    }
}
