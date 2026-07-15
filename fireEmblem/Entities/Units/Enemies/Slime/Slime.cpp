#include "Slime.hpp"

namespace Slimes
{
    Slime::Slime(GridHandlers::GridHandler& gridHandler, AttackManagers::AttackManager& attacks, float yPos, float xPos)
        : Enemy(gridHandler, attacks, yPos, xPos)
    {
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

        movementSpeed = 10;
        movement = 4;

        animations = &slimeAnimations;

    }

    // Håndterer bevegelse og angrep
    void Slime::PerformActions()
    {
        if (!path.empty())
        {
            attacks.CreateAttack(name, attackLevel, path[0].GetPosition());
        }
    }

    void Slime::Movement()
    {
        if (!path.empty())
        {
            static float calculatedPathX = 0;
            static float calculatedPathY = 0;

            if (cooldown == 0)
            {

                auto& tiles = gridHandler.RetrieveAllTiles();

                float currentTileY = path[numOfMoves].GetPosition().y;
                float currentTileX = path[numOfMoves].GetPosition().x;

                if (numOfMoves > 1)
                {
                    numOfMoves--;
                }
                else    // Hvis ferdig
                {
                    animations->setPositions(tileLocation);
                    std::cout << "1";
                }

                nextTileY = path[numOfMoves].GetPosition().y;
                nextTileX = path[numOfMoves].GetPosition().x;

                calculatedPathX = (nextTileX - currentTileX) / movementSpeed;
                calculatedPathY = (nextTileY - currentTileY) / movementSpeed;

                cooldown = movementSpeed;
            }

            cooldown--;

            if (algorithm.playerDetected == true)
            {
                animations->moveSprite({calculatedPathX, calculatedPathY});
            }
        }
    }

    void Slime::SetPathToPlayer()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();

        path = algorithm.CheckAvailableTiles(tileLocation.y, tileLocation.x, movement - 1, tiles);

        movementTime = path.size() * 10;    // Setter tiden som gåanimasjonen skal vare

        if (algorithm.playerDetected == true)
        {
            playerDetected = true;
            tileLocation.x = path[1].GetPosition().x / 50;
            tileLocation.y = path[1].GetPosition().y / 50;
        }
        else
        {
            playerDetected = false;
        }

        numOfMoves = path.size() - 1;

    }
}
