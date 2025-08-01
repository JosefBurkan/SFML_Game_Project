#include "Player.hpp"

namespace Players 
{
    // Initialiser spilleren, gridden den hører til og bevegelsen.
    Player::Player(GridGenerators::GridGenerator& gridReference, Maps::Map& map, GridMovements::GridMovement& gridMovement)
        : Unit(gridReference, map), gridMovement(gridMovement)
    {
        
        if (!texture.loadFromFile("prinsesse.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        name = "Player";
        healthPoints = 10;

        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});
        sprite->setPosition({5.f, 0.f});
    }


    // Håndtere bevegelsen av spilleren
    void Player::Movement() 
    {
        std::pair<float, float> retrievedTile = gridMovement.SelectedTilePos(); // Hent hvilken grid spilleren står på
        std::pair<float, float> selectedTile = gridMovement.RetrieveTile();
        
        float gridCurrentTileX = retrievedTile.first;
        float gridCurrentTileY = retrievedTile.second;


        // Velg spilleren, dersom ingen enheter har blitt valgt enda
        if (isSelected == false && preventSelect == true)
        {
            // Flytter musen til samme rute som spilleren
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                if (playerCurrentTileX == gridCurrentTileX && playerCurrentTileY == gridCurrentTileY)
                {
                    isSelected = true;
                    preventSelect = false;
                }
            }
        }
        // Sjekk om spilleren har blitt valgt
        else if (isSelected == true && preventSelect == true) 
        {
            auto& tiles = gridMovement.RetrieveAllTiles();

            // Sjekk om ruten er okkupert
            if (gridMovement.IsOccupied(tiles[selectedTile.first][selectedTile.second]) == false)
            {

                // Om 'A' trykkes, flytt spilleren
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) 
                {
                    isSelected = false;
                    preventSelect = false;
                    sprite->setPosition({gridCurrentTileX + 10, gridCurrentTileY});
                    playerCurrentTileX = gridCurrentTileX;
                    playerCurrentTileY = gridCurrentTileY;
                    gridMovement.UnSelectTile();
                    CheckForMapObjects();
                    // std::cout << tiles[selectedTile.first][selectedTile.second].isOccupiedByEnemy;
                }
            }
        }

        // Gjør at man ikke kan velge, og uvelge en karakter kjempefort ved å holde 'A'
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            preventSelect = true;
        }
        if (isSelected == true)
        {
            gridMovement.SelectTile();
        }
    }

}


