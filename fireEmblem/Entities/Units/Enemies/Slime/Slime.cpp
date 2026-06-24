#include "Slime.hpp"

namespace Slimes
{
    Slime::Slime(GridHandlers::GridHandler& gridHandler, Maps::Map& map, AttackManagers::AttackManager& attacks, float yPos, float xPos)
        : Enemy(gridHandler, map, attacks, yPos, xPos)
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Slime/Slime_Idle.png")) 
        {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!deathTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Slime/Slime_Death_Animation.png")) 
        {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!movingTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Slime/Slime_Moving.png")) 
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

        defaultDrawSpeed = 20;

        movingSpriteSizeY = 100;           // Størrelse på spritesheet
        movingSpriteSizeX = 150;


        movingDrawSpeed = 4;

        // Må reverseres her
        tileLocation.x = yPos / 50;
        tileLocation.y = xPos / 50;

        std::cout << "\nY Koordinat:" << tileLocation.y;

        tiles[tileLocation.y][tileLocation.x].SetUnit(this);
        tiles[tileLocation.y][tileLocation.x].IsOccupied = true;

        std::cout << "Stored ptr: " << tiles[tileLocation.y][tileLocation.x].unit << '\n';

        sprite.emplace(defaultTexture);
        sprite->setPosition({yPos, xPos});
        sprite->setTextureRect(sf::IntRect({0, 0}, {50, 50}));

        deathSprite.emplace(deathTexture);
        deathSprite->setPosition({yPos, xPos});
        deathSprite->setTextureRect(sf::IntRect({0, 0}, {50, 50}));

        movingSprite.emplace(movingTexture);
        movingSprite->setPosition({yPos, xPos});
        movingSprite->setTextureRect(sf::IntRect({0, 0}, {50, 50}));

        movementSpeed = 10;
        movement = 4;

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
                else    // Hvis ferdig
                {
                }

                nextTileY = pathToPlayer[numOfMoves].GetPosition().y;
                nextTileX = pathToPlayer[numOfMoves].GetPosition().x;

                calculatedPathX = (nextTileX - currentTileX) / movementSpeed;
                calculatedPathY = (nextTileY - currentTileY) / movementSpeed;

                cooldown = movementSpeed;
            }

            cooldown--;

            if (algorithm.playerDetected == true)
            {
                movingSprite->move({calculatedPathX, calculatedPathY});
                deathSprite->setPosition({sprite->getPosition().x, sprite->getPosition().y});
            }
        }
    }

    void Slime::SetPathToPlayer()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();

        pathToPlayer = algorithm.CheckAvailableTiles(sprite->getPosition().y / 50, sprite->getPosition().x / 50, movement - 1, tiles);

        movementTime = pathToPlayer.size() * 10;    // Setter tiden som gåanimasjonen skal vare

        if (algorithm.playerDetected == true)
        {
            playerDetected = true;
            tileLocation.x = pathToPlayer[1].GetPosition().x / 50;
            tileLocation.y = pathToPlayer[1].GetPosition().y / 50;
            sprite->setPosition(pathToPlayer[1].GetPosition());
        }
        else
        {
            playerDetected = false;
        }

        numOfMoves = pathToPlayer.size() - 1;

    }
}
