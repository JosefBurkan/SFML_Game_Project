#include "Player.hpp"

namespace Players 
{
    // Initialiser spilleren, gridden den hører til og bevegelsen.
    Player::Player(GridGenerators::GridGenerator& gridReference, Maps::Map& map, 
                    AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler)
        : Unit(gridReference, map, attacks), GridHandler(GridHandler)
    {
        if (!texture.loadFromFile(std::string(ASSETS_DIR) + "Prinsesse-50x50.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        name = "Player";
        healthPoints = 4;
        maxHealth = healthPoints;
        texture.setSmooth(false);

        type = "Player";
        speed = 3;

        sprite.emplace(texture);
        sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));
        sprite->setPosition({0.f, 100.f});
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
        auto& tiles = GridHandler.RetrieveAllTiles();

        std::pair<float, float> retrievedTile = GridHandler.SelectedTilePos(); // Hent hvilken rute spilleren står på
        
        float gridCurrentTileX = retrievedTile.first;
        float gridCurrentTileY = retrievedTile.second;
        
        state = "Neutral";
        menu.show = false;
        inMenu = false;
        GridHandler.rangeX = 0;
        GridHandler.rangeY = 0;
        isSelected = false;
        preventSelect = false;
        algorithm.CleanGrid(tiles, gridCurrentTileY, gridCurrentTileX);     // Fjern rutene 
    }   



    void Player::DrawUI(sf::RenderWindow& window)
    {
        menu.Draw(window);
        attacks.Draw(window);
    }

    // Håndtere bevegelsen av spilleren
    void Player::Movement()
    {
        std::pair<float, float> retrievedTile = GridHandler.SelectedTilePos(); // Hent hvilken rute spilleren står på
        std::pair<float, float> selectedTile = GridHandler.RetrieveTile();

        std::pair<float, float> retrievedTileIndex = GridHandler.RetrieveTileIndex();
        
        float gridCurrentTileX = retrievedTile.second;
        float gridCurrentTileY = retrievedTile.first;

        // Velg spilleren, dersom ingen enheter har blitt valgt enda
        if (isSelected == false && preventSelect == true && inMenu == false && state == "Neutral")
        {
            auto& tiles = GridHandler.RetrieveAllTiles();

            // Flytter musen til samme rute som spilleren
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                std::cout << gridCurrentTileY << " " << playerCurrentTileY <<"\n";

                // Står spilleren på samme rute som er valgt på rutefeltet
                if (playerCurrentTileY == gridCurrentTileY && playerCurrentTileX == gridCurrentTileX)
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
                algorithm.CleanGrid(tiles, gridCurrentTileX, gridCurrentTileY);
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
                    sprite->setPosition({gridCurrentTileX, gridCurrentTileY});
                    playerCurrentTileX = gridCurrentTileX;
                    playerCurrentTileY = gridCurrentTileY;
                    algorithm.CleanGrid(tiles, gridCurrentTileX, gridCurrentTileY);     // Fjern rutene 
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
            Attacks::Attack newAttack{gridCurrentTileX, gridCurrentTileY};                          
            attacks.CreateAttack(newAttack);
            state = "Finished";

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


