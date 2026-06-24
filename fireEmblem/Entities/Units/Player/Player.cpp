#include "Player.hpp"

namespace Players 
{
    // Initialiser spilleren, gridden den hører til og bevegelsen.
    Player::Player(GridHandlers::GridHandler& gridHandler, Maps::Map& map, 
                    AttackManagers::AttackManager& attacks)
        : Unit(gridHandler, map, attacks)
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/Prinsesse-50x50.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!attackTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/Princess_Shoot.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!deathTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/prinsesse_death.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!movingTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/Princess_Running.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        if (!iconTextureLarge.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/prinsesse_ansikt.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        name = "Player";
        currentHealth = 4;
        maxHealth = currentHealth;
        defaultTexture.setSmooth(false);
        attackTexture.setSmooth(false);

        type = "Player";
        speed = 3;

        tileLocation.y = 2;
        tileLocation.x = 0;

        sprite.emplace(defaultTexture);
        attackSprite.emplace(attackTexture);
        deathSprite.emplace(deathTexture);
        movingSprite.emplace(movingTexture);
        
        sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));
        sprite->setPosition(tileLocation * 50.f);

        movingSprite->setPosition(tileLocation * 50.f);

        attackSprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));

        previousPosition = sprite->getPosition();

        attackingDrawSpeed = 7;
        attackTimer = 42;   
        maxAttackTimer = attackTimer;

        attackSpawnTimer = 40;   
        maxAttackSpawnTimer = attackSpawnTimer;

        experienceToLevelUp *= level;

        movementSpeed = 10;
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

    void Player::Attack(sf::Vector2f position)
    {
        attacks.CreateRangedAttack(name, attackLevel, position, {6, 0});
        attackSpawnTimer = maxAttackSpawnTimer;
    }

    void Player::CancelSelect()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();

        selectedTile = gridHandler.GetSelectedTile();

        Tiles::Tile tile = gridHandler.GetSelectedTile(); // Hent hvilken rute som er valgt
        
        gridCurrentTile = tile.GetPosition() / 50.f;
        
        menu.show = false;
        skills.show = false;
        inMenu = false;

        finishedMoving = false;

        tile.UnSelect();
        algorithm.CleanGrid(tiles);     // Fjern de markerte rutene 

        sprite->setPosition({previousPosition});
        attackSprite->setPosition({previousPosition});
        RevertOccupation();

        tileLocation.y = previousPosition.y / 50;
        tileLocation.x = previousPosition.x / 50;

        state = "Neutral";
    }   

    void Player::ConfirmMovement()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();

        selectedTile = gridHandler.GetSelectedTile();    

        SetPathToSelectedTile();

        previousPosition = sprite->getPosition();

        // Alt relatert til rutenettet
        isSelected = false;
        preventSelect = false;

        algorithm.CleanGrid(tiles);     // Fjern rutene

        CheckForMapObjects();

        // Alt relatert til menyene pathToPlayer
        menuCooldown = 30;
        menu.show = true;
        inMenu = true;
        menu.SetPosition((tileLocation.x * 50) - 120, (tileLocation.y * 50) - 50);
        skills.SetPosition((tileLocation.x * 50) - 120, (tileLocation.y * 50) - 50);

        state = "Moving";
    }

    void Player::SmoothMove()
    {
        if (!path.empty())
        {
            if (moving <= 0)
            {
                auto& tiles = gridHandler.RetrieveAllTiles();

                // Her så må currentTile settes til sine motsatte verdier, da mitt tilesystem og Vector2f fungerer motsatt vei
                float currentTileY = path[numOfMoves].GetPosition().x;
                float currentTileX = path[numOfMoves].GetPosition().y;

                if (numOfMoves > 0)
                {
                    numOfMoves--;
                }
                else
                {
                    finishedMoving = true;
                }

                float nextTileY = path[numOfMoves].GetPosition().x;
                float nextTileX = path[numOfMoves].GetPosition().y;

                calculatedPathX = (nextTileX - currentTileX) / movementSpeed;
                calculatedPathY = (nextTileY - currentTileY) / movementSpeed;

                moving = movementSpeed;
            }

            moving--;

            if (pathAlgorithm.playerDetected == true)
            {
                movingSprite->move({calculatedPathY, calculatedPathX});
            }
        }
    }

    void Player::SetPathToSelectedTile()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();

        path = pathAlgorithm.CheckAvailableTiles(sprite->getPosition(), tiles);

        moving = 0;
        numOfMoves = path.size() - 1;

        movementTime = path.size() * 10;    // Setter tiden som gåanimasjonen skal vare

        for (int i = 0; i < path.size(); i++)
        {
            std::cout << " X: " << path[i].GetPosition().x << " Y: " << path[i].GetPosition().y;
        }
    }

    void Player::SetTileToOccupied()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();

        tiles[tileLocation.y][tileLocation.x].RemoveUnit();

        tiles[gridCurrentTile.y][gridCurrentTile.x].SetUnit(this);

        tiles[gridCurrentTile.y][gridCurrentTile.x].isSelected = false;

    }

    void Player::RevertOccupation()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();

        tiles[gridCurrentTile.y][gridCurrentTile.x].RemoveUnit();

        tiles[tileLocation.y][tileLocation.x].SetUnit(this);

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
        auto& tiles = gridHandler.RetrieveAllTiles();

        selectedTile = gridHandler.GetSelectedTile();     

        gridCurrentTile = selectedTile.GetPosition() / 50.f;

        // Velg spilleren, dersom ingen enheter har blitt valgt enda
        if (!isSelected && preventSelect && !inMenu && state == "Neutral")
        {
            // Flytter musen til samme rute som spilleren
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                tileLocation.y = sprite->getPosition().y / 50;
                tileLocation.x = sprite->getPosition().x / 50;

                int roundedY = static_cast<int>(std::round(tileLocation.y));
                int roundedX = static_cast<int>(std::round(tileLocation.x));

                // Står spilleren på samme rute som er valgt på rutefeltet
                if (roundedY == gridCurrentTile.y && roundedX == gridCurrentTile.x)
                {
                    isSelected = true;
                    preventSelect = false;
                    algorithm.CreateRoute(sprite->getPosition() / 50.f, movement, tiles);
                    state = "Selected";
                }
            }
        }
        // Sjekk om spilleren har blitt valgt
        else if (isSelected == true && preventSelect == true) 
        {
            // Sjekk om ruten er okkupert
            if (!gridHandler.IsOccupied(selectedTile)
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
                std::cout << "\nCD: " << menuCooldown;
                std::cout << "\nBevegelse: " << finishedMoving;
                
                menu.show = false;

                deathSprite->setPosition(tileLocation * 50.f);
                attackSprite->setPosition(tileLocation * 50.f);
                 
                switch(menu.index)
                {
                    case 0:
                        state = "Attack";
                        inMenu = false;
                        sprite->setPosition({gridCurrentTile * 50.f});    // Unngå at spiller står på desimalverdi
                        attackSprite->setPosition({gridCurrentTile * 50.f});   
                        deathSprite->setPosition({gridCurrentTile * 50.f});    
                        movingSprite->setPosition({gridCurrentTile * 50.f});    
                        previousPosition = sprite->getPosition();
                        SetTileToOccupied();

                        finishedMoving = true;
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
                Attack(gridCurrentTile * 50.f);
            }
        }
        // Gjør at man ikke kan velge, og uvelge en karakter kjempefort ved å holde 'A'
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            preventSelect = true;
        }
        if (isSelected)
        {
            gridHandler.ColorTile();
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

