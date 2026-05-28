#include "Player.hpp"

namespace Players 
{
    // Initialiser spilleren, gridden den hører til og bevegelsen.
    Player::Player(GridGenerators::GridGenerator& gridReference, Maps::Map& map, 
                    AttackManagers::AttackManager& attacks, GridHandlers::GridHandler& GridHandler)
        : Unit(gridReference, map, attacks), GridHandler(GridHandler)
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/Prinsesse-50x50.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!attackTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/Princess_Shoot.png")) {
            throw std::runtime_error("Failed to load texture!");
        }


        name = "Player";
        currentHealth = 4;
        maxHealth = currentHealth;
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

        experienceToLevelUp *= level;

        previousPosition = sprite->getPosition();
    }

    std::pair<int, int> Player::TransformPositionToIndex(float spriteY, float spriteX)
    {
        return {spriteY/50, spriteX/50};
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

        attacks.CreateRangedAttack(name, attackLevel, spawnLocationX, spawnLocationY, {6, 0});
        attackSpawnTimer = maxAttackSpawnTimer;
    }

    void Player::CancelSelect()
    {
        auto& tiles = GridHandler.RetrieveAllTiles();

        Tiles::Tile tile = GridHandler.GetSelectedTile(); // Hent hvilken rute spilleren står på
        
        gridCurrentTileX = tile.GetPosition().second;
        gridCurrentTileY = tile.GetPosition().first;
        
        state = "Neutral";

        menu.show = false;
        skills.show = false;
        inMenu = false;
        finishedMoving = false;

        isSelected = false;
        preventSelect = false;
        SetTileToUnOccupied();
        tile.UnSelect();
        algorithm.CleanGrid(tiles, gridCurrentTileY, gridCurrentTileX);     // Fjern de markerte rutene 

        sprite->setPosition({previousPosition});
        attackSprite->setPosition({previousPosition});
        SetTileToOccupied();

        playerCurrentTileY = previousPosition.y / 50;
        playerCurrentTileX = previousPosition.x / 50;
    }   

    void Player::ConfirmMovement()
    {

        auto& tiles = GridHandler.RetrieveAllTiles();

        selectedTile = GridHandler.GetSelectedTile();    

        SetPathToSelectedTile();

        previousPosition = sprite->getPosition();

        // Alt relatert til rutenettet
        isSelected = false;
        preventSelect = false;

        algorithm.CleanGrid(tiles, previousPosition.y, previousPosition.x);     // Fjern rutene 

        CheckForMapObjects();

        // Alt relatert til menyene pathToPlayer
        selectedTile.IsOccupiedByPlayer = true;
        menuCooldown = 30;
        menu.show = true;
        inMenu = true;
        menu.SetPosition(sprite->getPosition().x - 120, sprite->getPosition().y - 50);
        skills.SetPosition(sprite->getPosition().x - 120, sprite->getPosition().y - 50);

        state = "Moving";

    }

    void Player::SmoothMove()
    {
        if (!path.empty())
        {
            if (moving <= 0)
            {
                auto& tiles = gridGenerator.RetrieveAllTiles();

                float currentTileY = path[numOfMoves].GetPosition().first;
                float currentTileX = path[numOfMoves].GetPosition().second;

                if (numOfMoves < path.size() - 1)
                {
                    numOfMoves++;
                }
                else
                {
                    finishedMoving = true;
                }

                float nextTileY = path[numOfMoves].GetPosition().first;
                float nextTileX = path[numOfMoves].GetPosition().second;

                calculatedPathX = (nextTileX - currentTileX) / movementSpeed;
                calculatedPathY = (nextTileY - currentTileY) / movementSpeed;

                moving = movementSpeed;
            }

            moving--;

            if (pathAlgorithm.playerDetected == true)
            {
                sprite->move({calculatedPathX, calculatedPathY});

                deathSprite->setPosition({sprite->getPosition().x, sprite->getPosition().y});
                attackSprite->setPosition({sprite->getPosition().x, sprite->getPosition().y});

            }

        }
    }

    void Player::SetPathToSelectedTile()
    {
        auto& tiles = gridGenerator.RetrieveAllTiles();

        path = pathAlgorithm.CheckAvailableTiles(selectedTile.GetPosition().first / 50, selectedTile.GetPosition().second / 50, tiles);

        moving = 0;
        numOfMoves = 0;

        movementTime = path.size() * 10;    // Setter tiden som gåanimasjonen skal vare

        for (int i = 0; i < path.size(); i++)
        {
            std::cout << " X: " << path[i].GetPosition().second << " Y: " << path[i].GetPosition().first;
        }
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

        selectedTile = GridHandler.GetSelectedTile();     

        gridCurrentTileX = selectedTile.GetPosition().second / 50;
        gridCurrentTileY = selectedTile.GetPosition().first / 50;

        // Velg spilleren, dersom ingen enheter har blitt valgt enda
        if (!isSelected && preventSelect && !inMenu && state == "Neutral")
        {
            // Flytter musen til samme rute som spilleren
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                playerCurrentTileY = sprite->getPosition().y / 50;
                playerCurrentTileX = sprite->getPosition().x / 50;

                int roundedY = static_cast<int>(std::round(playerCurrentTileY));
                int roundedX = static_cast<int>(std::round(playerCurrentTileX));

                // Står spilleren på samme rute som er valgt på rutefeltet
                if (roundedY == gridCurrentTileY && roundedX == gridCurrentTileX)
                {
                    previousTilePosition = {playerCurrentTileY, playerCurrentTileX};
                    isSelected = true;
                    preventSelect = false;
                    algorithm.CreateRoute(gridCurrentTileY, gridCurrentTileX, movement, tiles);
                    state = "Selected";
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
            {
                CancelSelect();
            }
        }
        // Sjekk om spilleren har blitt valgt
        else if (isSelected == true && preventSelect == true) 
        {
            // Sjekk om ruten er okkupert
            if (!GridHandler.IsOccupied(selectedTile)
             && selectedTile.inRange)
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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && menuCooldown <= 0 && finishedMoving)
            {
                menu.show = false;
                 
                switch(menu.index)
                {
                    case 0:
                        state = "Attack";
                        inMenu = false;
                        sprite->setPosition({gridCurrentTileX * 50, gridCurrentTileY * 50});    // Unngå at spiller står på desimalverdi
                        tiles[previousPosition.y / 50][previousPosition.x / 50].IsOccupiedByPlayer = false;
                        tiles[gridCurrentTileY][gridCurrentTileX].IsOccupiedByPlayer = true;
                        finishedMoving = false;
                        break;
                    case 1:
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
                Attack(gridCurrentTileX * 50, gridCurrentTileY * 50);
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

    // Hent dataen lagret i .txt fila til karakteren
    void Player::ReadData()
    {
        std::ifstream file(std::string(ASSETS_DIR) + "Units/Princess/SavedData.txt");

        if (!file)
        {
            throw std::runtime_error("failed to load texture! ");
        }

        std::string word = "";

        // 'r' står for retrieved
        int r_level = 0;
        int r_experience = 0;
        int r_maxHealth = 0;
        int r_currentHealth = 0;
        int r_attackLevel = 0;
        int r_speed = 0;

        int index = 0;

        std::array stats = {r_level, r_experience, r_maxHealth, r_currentHealth, r_attackLevel, r_speed};

        while (file >> word) 
        {

            file >> stats[index];
            index++;
        }

        SetData(stats);
    }

    void Player::SetData(std::array<int, 6> stats)
    {
        level = stats[0];
        experience = stats[1];
        maxHealth = stats[2];
        currentHealth = stats[3];
        attackLevel = stats[4];
        speed = stats[5];
    }

    void Player::SaveData()
    {

    }

}

