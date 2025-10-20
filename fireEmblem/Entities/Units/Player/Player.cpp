#include "Player.hpp"

namespace Players 
{
    // Initialiser spilleren, gridden den hører til og bevegelsen.
    Player::Player(GridGenerators::GridGenerator& gridReference, Maps::Map& map, 
                    AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler)
        : Unit(gridReference, map, attacks), GridHandler(GridHandler)
    {
        if (!texture.loadFromFile(std::string(ASSETS_DIR) + "Prinsesse.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        name = "Player";
        healthPoints = 3;
        type = "Player";

        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});
        sprite->setPosition({0.f, 0.f});
    }

    std::pair<int, int> Player::TransformPositionToIndex(float spriteY, float spriteX)
    {
        return {spriteY/50, spriteX/50};
    }

    // Sjekke om spilleren ikke er i et angrep, blir skadet etter noe tilsvarende
    bool Player::IsPlayerStateReady()
    {
        if (menu.show == false)
        {
            return false;
        }
        else
        {
            return true;
        }
    }    

    void Player::CancelSelect()
    {
        state = "Neutral";
        menu.show = false;
        inMenu = false;
        GridHandler.rangeX = 0;
        GridHandler.rangeY = 0;
        currentTurn = false;
        isSelected = false;
        preventSelect = false;
    }   

    void Player::Draw(sf::RenderWindow& window) 
    {
        window.draw(*sprite);
        menu.Draw(window);
        attacks.Draw(window);
    }

    // Håndtere bevegelsen av spilleren
    void Player::Movement() 
    {
        std::pair<float, float> retrievedTile = GridHandler.SelectedTilePos(); // Hent hvilken rute spilleren står på
        std::pair<float, float> selectedTile = GridHandler.RetrieveTile();

        std::pair<float, float> retrievedTileIndex = GridHandler.RetrieveTileIndex();
        
        float gridCurrentTileX = retrievedTile.first;
        float gridCurrentTileY = retrievedTile.second;

        // Velg spilleren, dersom ingen enheter har blitt valgt enda
        if (isSelected == false && preventSelect == true && inMenu == false && state == "Neutral")
        {
            auto& tiles = GridHandler.RetrieveAllTiles();

            // Flytter musen til samme rute som spilleren
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {

                // Står spilleren på samme rute som er valgt på rutefeltet
                if (playerCurrentTileX == gridCurrentTileX && playerCurrentTileY == gridCurrentTileY)
                {
                    tiles[selectedTile.first][selectedTile.second].IsOccupiedByPlayer = false;
                    isSelected = true;
                    preventSelect = false;
                    algorithm.CheckAvailableTiles(retrievedTileIndex.first, retrievedTileIndex.second, movement, tiles);
                    state = "Selected";
                }
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
            {
                tiles[selectedTile.first][selectedTile.second].IsOccupiedByPlayer = true;
                CancelSelect();
                algorithm.CleanGrid(tiles, gridCurrentTileY, gridCurrentTileX);
            }
        }
        // Sjekk om spilleren har blitt valgt
        else if (isSelected == true && preventSelect == true) 
        {
            auto& tiles = GridHandler.RetrieveAllTiles();

            // Koordinatene til spilleren, i form av index
            std::pair<int, int> coordinates = TransformPositionToIndex(sprite->getPosition().x, sprite->getPosition().y);
            
            // Sjekk om ruten er okkupert
            if (GridHandler.IsOccupied(tiles[selectedTile.first][selectedTile.second]) == false
             && tiles[selectedTile.first][selectedTile.second].inRange == true)
            {
                // Om 'A' trykkes, flytt spilleren
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) 
                {
                    tiles[selectedTile.first][selectedTile.second].IsOccupiedByPlayer = true;
                    isSelected = false;
                    preventSelect = false;
                    sprite->setPosition({gridCurrentTileY + 10, gridCurrentTileX});
                    playerCurrentTileX = gridCurrentTileX;
                    playerCurrentTileY = gridCurrentTileY;
                    algorithm.CleanGrid(tiles, gridCurrentTileY, gridCurrentTileX);     // Fjern rutene 
                    CheckForMapObjects();
                    menuCooldown = 0;
                    attackCooldown = 0;
                    menu.show = true;
                    inMenu = true;
                    menu.SetPosition(sprite->getPosition().x - 120, sprite->getPosition().y - 50);
                }
            }
        }
        // Trykk 'X' for å lukke menyen
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
        {
            CancelSelect();
        }

        // Funksjonalitet for de ulike knappene å trykke på inne i menyen
        if (menu.show == true)
        {            
            menuCooldown++;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && menu.menuContentsIndex == 0 && menuCooldown >= 30)
            {
                state = "Attack";
                menu.show = false;
                inMenu = false;
            }
        }
        // Lag en ny hitbox, så sett dens posisjon med "CreateHitbox"
        if (state == "Attack" && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            attackCooldown++;
            Attacks::Attack newAttack{gridCurrentTileY, gridCurrentTileX};                          
            attacks.CreateAttack(newAttack);
            state = "Neutral";
            currentTurn = false;

        }
        // Gjør at man ikke kan velge, og uvelge en karakter kjempefort ved å holde 'A'
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            preventSelect = true;
        }
        if (isSelected == true)
        {
            GridHandler.SelectTile();
        }
    }

}


