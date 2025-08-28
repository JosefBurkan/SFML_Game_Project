#include "Player.hpp"

namespace Players 
{
    // Initialiser spilleren, gridden den hører til og bevegelsen.
    Player::Player(GridGenerators::GridGenerator& gridReference, Maps::Map& map, 
                    AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler)
        : Unit(gridReference, map, attacks), GridHandler(GridHandler)
    {
        
        if (!texture.loadFromFile("prinsesse.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        name = "Player";
        healthPoints = 10;

        sprite.emplace(texture);
        sprite->setScale({3.f, 3.f});
        sprite->setPosition({0.f, 0.f});
    }

    std::pair<int, int> Player::TransformPositionToIndex(float spriteX, float spriteY)
    {
        return {spriteX/50, spriteY/50};
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

    void Player::DrawUI(sf::RenderWindow& window)
    {
        menu.Draw(window);
    }
    void Player::Draw(sf::RenderWindow& window) 
    {
        window.draw(*sprite);
        menu.Draw(window);
        attacks.Draw(window);
    }

    void Player::Attack()
    {

    }

    // Håndtere bevegelsen av spilleren
    void Player::Movement() 
    {
        std::pair<float, float> retrievedTile = GridHandler.SelectedTilePos(); // Hent hvilken grid spilleren står på
        std::pair<float, float> selectedTile = GridHandler.RetrieveTile();
        
        float gridCurrentTileX = retrievedTile.first;
        float gridCurrentTileY = retrievedTile.second;

        menu.SetPosition(sprite->getPosition().x - 120, sprite->getPosition().y - 50);

        // Velg spilleren, dersom ingen enheter har blitt valgt enda
        if (isSelected == false && preventSelect == true && inMenu == false && state == "Neutral")
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
            auto& tiles = GridHandler.RetrieveAllTiles();

            // Koordinatene til spilleren, i form av index
            std::pair<int, int> coordinates = TransformPositionToIndex(sprite->getPosition().x, sprite->getPosition().y);

            // Lys opp ruter som spilleren kan bevege seg til
            /*
            for (int i = 0; i < movement; i++)
            {
                if (tiles[coordinates.second][coordinates.first - i].RetrieveTilePos().first > i)
                {
                    tiles[coordinates.second][coordinates.first + i].Highlight(coordinates, tiles.size(), tiles[0].size());
                    tiles[coordinates.second][coordinates.first - i - 1].Highlight(coordinates, tiles.size(), tiles[0].size());
                }
            }
            */

            // Sjekk om ruten er okkupert
            if (GridHandler.IsOccupied(tiles[selectedTile.first][selectedTile.second]) == false)
            {
                // Om 'A' trykkes, flytt spilleren
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) 
                {
                    isSelected = false;
                    preventSelect = false;
                    menu.show = true;
                    inMenu = true;
                    sprite->setPosition({gridCurrentTileX + 10, gridCurrentTileY});
                    playerCurrentTileX = gridCurrentTileX;
                    playerCurrentTileY = gridCurrentTileY;
                    GridHandler.UnSelectTile();
                    CheckForMapObjects();
                    menuCooldown = 0;
                    attackCooldown = 0;
                }
            }
        }

        // Trykk 'X' for å lukke menyen
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
        {
            state = "Neutral";
            menu.show = false;
            inMenu = false;
            GridHandler.rangeX = 0;
            GridHandler.rangeY = 0;
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
            state = "Neutral";

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


