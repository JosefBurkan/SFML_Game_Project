#include "Player.hpp"

namespace Players 
{
    // Initialiser spilleren, gridden den hører til og bevegelsen.
    Player::Player(std::string name, int healthPoints, std::string spritePath, GridGenerators::GridGenerator& gridReference, GridMovements::GridMovement& gridMovement, Maps::Map& map)
        : Unit(name, healthPoints, spritePath, gridReference), gridMovement(gridMovement), map(map) // Fortell hvilken grid som brukes
    {
        
        if (!texture.loadFromFile(spritePath)) {
            throw std::runtime_error("Failed to load texture!");
        }

        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});
        sprite->setPosition({5.f, 0.f});
    }

    // Tegn spilleren sin sprite
    void Player::Draw(sf::RenderWindow& window) 
    {
        window.draw(*sprite);
    }

    // Sjekk hvilket baneobjekt spilleren står på, feks. skog
    void Player::CheckForMapObjects()
    {
        for (auto& object : map.mapObjects)
        {
            if (sprite->getPosition().x == object.printPos().first + 10 && sprite->getPosition().y == object.printPos().second)
            {
                std::cout << "Nå står du på: " << object.name << "\n";
            }
        }
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


