#include "Player.hpp"

namespace Players 
{
    // Initialiser spilleren, gridden den hører til og bevegelsen.
    Player::Player(GridGenerators::GridGenerator& gridReference, Maps::Map& map, 
                    AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler)
        : Unit(gridReference, map, attacks), GridHandler(GridHandler)
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Prinsesse-50x50.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!attackTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess_Shoot.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        name = "Player";
        healthPoints = 4;
        maxHealth = healthPoints;
        defaultTexture.setSmooth(false);
        attackTexture.setSmooth(false);

        type = "Player";
        speed = 3;

        sprite.emplace(defaultTexture);
        attackSprite.emplace(attackTexture);
        
        sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));
        attackSprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));
        sprite->setPosition({0.f, 100.f});

        attackingDrawSpeed = 7;
        attackTimer = 42;   
        maxAttackTimer = attackTimer;

        attackSpawnTimer = 40;   
        maxAttackSpawnTimer = attackSpawnTimer;

    }

    std::pair<int, int> Player::TransformPositionToIndex(float spriteY, float spriteX)
    {
        return {spriteY/50, spriteX/50};
    }

    void Player::CancelSelect()
    {
        auto& tiles = GridHandler.RetrieveAllTiles();

        std::pair<float, float> retrievedTile = GridHandler.SelectedTilePos(); // Hent hvilken rute spilleren står på
        
        float gridCurrentTileX = retrievedTile.first;
        float gridCurrentTileY = retrievedTile.second;
        
        state = "Neutral";

        menu.show = false;
        skills.show = false;
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
        skills.Draw(window);
        attacks.Draw(window);
    }

    void Player::Attack(float spawnLocationX, float spawnLocationY)
    {
        float x = sprite->getPosition().x;
        float y = sprite->getPosition().y;

        attacks.CreateRangedAttack(spawnLocationX, spawnLocationY, {6, 0});
        attackSpawnTimer = maxAttackSpawnTimer;
    }

    void Player::ConfirmMovement()
    {
        auto& tiles = GridHandler.RetrieveAllTiles();

        retrievedTile = GridHandler.SelectedTilePos(); 
        selectedTile = GridHandler.RetrieveTile();     

        float gridCurrentTileX = retrievedTile.second;
        float gridCurrentTileY = retrievedTile.first;

        // Alt relatert til rutenettet
        isSelected = false;
        preventSelect = false;
        sprite->setPosition({gridCurrentTileX, gridCurrentTileY});
        attackSprite->setPosition({gridCurrentTileX, gridCurrentTileY});
        playerCurrentTileX = gridCurrentTileX;
        playerCurrentTileY = gridCurrentTileY;
        algorithm.CleanGrid(tiles, gridCurrentTileX, gridCurrentTileY);     // Fjern rutene 
        CheckForMapObjects();
        SetTileToOccupied();    


        // Alt relatert til menyene
        menuCooldown = 30;
        menu.show = true;
        inMenu = true;
        menu.SetPosition(sprite->getPosition().x - 120, sprite->getPosition().y - 50);
        skills.SetPosition(sprite->getPosition().x - 120, sprite->getPosition().y - 50);
    }

    void Player::SetTileToUnOccupied()
    {
        auto& tiles = gridGenerator.RetrieveAllTiles();
        tiles[sprite->getPosition().y / 50][sprite->getPosition().x / 50].IsOccupiedByPlayer = false;
    }

    void Player::SetTileToOccupied()
    {
        auto& tiles = gridGenerator.RetrieveAllTiles();
        tiles[sprite->getPosition().y / 50][sprite->getPosition().x / 50].IsOccupiedByPlayer = true;
    }

    bool Player::IsMenuOpen()
    {
        if (menu.show == true || skills.show == true)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    // Håndtere bevegelsen av spilleren
    void Player::Movement()
    {
        auto& tiles = GridHandler.RetrieveAllTiles();

        retrievedTile = GridHandler.SelectedTilePos(); 
        selectedTile = GridHandler.RetrieveTile();     

        float gridCurrentTileX = retrievedTile.second;
        float gridCurrentTileY = retrievedTile.first;

        // Velg spilleren, dersom ingen enheter har blitt valgt enda
        if (isSelected == false && preventSelect == true && inMenu == false && state == "Neutral")
        {
            // Flytter musen til samme rute som spilleren
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                // Står spilleren på samme rute som er valgt på rutefeltet
                if (playerCurrentTileY == gridCurrentTileY && playerCurrentTileX == gridCurrentTileX)
                {
                    SetTileToUnOccupied();
                    isSelected = true;
                    preventSelect = false;
                    algorithm.CheckAvailableTiles(retrievedTile.first, retrievedTile.second, movement, tiles);
                    state = "Selected";
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
            {
                CancelSelect();
                algorithm.CleanGrid(tiles, gridCurrentTileX, gridCurrentTileY);
            }
        }
        // Sjekk om spilleren har blitt valgt
        else if (isSelected == true && preventSelect == true) 
        {
            // Koordinatene til spilleren, i form av index
            std::pair<int, int> coordinates = TransformPositionToIndex(sprite->getPosition().x, sprite->getPosition().y);
            
            // Sjekk om ruten er okkupert
            if (!GridHandler.IsOccupied(tiles[selectedTile.first][selectedTile.second])
             && tiles[selectedTile.first][selectedTile.second].inRange)
            {
                // Om 'A' trykkes, flytt spilleren
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) 
                {
                    ConfirmMovement();
                }
            }
        }

        // Trykk 'X' for å lukke menyen, og "deselecte" karakteren
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
        {
            CancelSelect();
        }

        // Funksjonalitet for de ulike knappene å trykke på inne i menyen
        if (IsMenuOpen())
        {            
            menuCooldown--;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && menuCooldown <= 0)
            {
                menu.show = false;
                 
                switch(menu.index)
                {
                    case 0:
                        state = "Attack";
                        inMenu = false;
                        break;
                    case 1:
                        std::cout << "Menyen har blitt åpnet";
                        skills.show = true;
                        break;
                    case 2:
                        std::cout << "???";
                        break;
                }
            }
        }
        // Lag en ny hitbox, så sett dens posisjon med "CreateHitbox"
        if (state == "Attack" && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            state = "Attacking"; 
            ResetAnimations();
        }
        else if (state == "Attacking")
        {
            attackSpawnTimer--;

            if (attackSpawnTimer <= 0)
            {
                Attack(gridCurrentTileX, gridCurrentTileY);
            }
        }
        // Gjør at man ikke kan velge, og uvelge en karakter kjempefort ved å holde 'A'
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            preventSelect = true;
        }
        if (isSelected)
        {
            GridHandler.ColorTile();
        }
    }

}

