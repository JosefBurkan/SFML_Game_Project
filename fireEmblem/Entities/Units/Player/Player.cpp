#include "Player.hpp"
#include "fstream"

namespace Players 
{
    // Initialiser spilleren, gridden den hører til og bevegelsen
    Player::Player(GridHandlers::GridHandler& gridHandler, 
                    AttackManagers::AttackManager& attacks)
        : Unit(gridHandler, attacks)
    {
        if (!iconTextureLarge.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/prinsesse_ansikt.png")) {
            throw std::runtime_error("Failed to load texture!");
        }

        name = "Player";
        currentHealth = 4;
        maxHealth = currentHealth;

        type = "Player";
        speed = 3;

        tileLocation.y = 2;
        tileLocation.x = 0;


        previousPosition = tileLocation;

        attackTimer = 42;   
        maxAttackTimer = attackTimer;

        attackSpawnTimer = 40;   
        maxAttackSpawnTimer = attackSpawnTimer;

        experienceToLevelUp *= level;

        movementSpeed = 10;
    }

    void Player::DrawUI(sf::RenderWindow& window)
    {
        menu.Draw(window);
        skills.Draw(window);
        attacks.Draw(window);
    }

    void Player::Attack(sf::Vector2f position)
    {
        position.x += 30.f;
        attacks.CreateRangedAttack(name, attackLevel, position, {6, 0});
        std::cout << "\nAngrip!";
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

        RevertOccupation();

        tileLocation.y = previousPosition.y / 50;
        tileLocation.x = previousPosition.x / 50;

        state = State::idle;
    }   

    void Player::ConfirmMovement()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();

        selectedTile = gridHandler.GetSelectedTile();    

        SetPathToSelectedTile();

        previousPosition = tileLocation;

        tileLocation = selectedTile.GetPosition() / 50.f;

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

        state = State::moving;
    }

    void Player::SmoothMove()
    {
        if (!path.empty())
        {
            static float calculatedPathX = 0;
            static float calculatedPathY = 0;

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
                    animations->resetAnimations();
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
                ReverseSprite(calculatedPathY, calculatedPathX);
                animations->moveSprite({calculatedPathY, calculatedPathX});
            }
        }
    }

    void Player::SetPathToSelectedTile()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();

        path = pathAlgorithm.CheckAvailableTiles(tileLocation, tiles);

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

        std::cout << " " << previousPosition.y << previousPosition.x;

        tiles[previousPosition.y][previousPosition.x].RemoveUnit();
        tiles[previousPosition.y][previousPosition.x].isSelected = false;

        tiles[gridCurrentTile.y][gridCurrentTile.x].SetUnit(this);
        tiles[gridCurrentTile.y][gridCurrentTile.x].isSelected = true;

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
        // Trykk 'X' for å lukke menyen, og "deselecte" karakteren
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
        {
            CancelSelect();
        }

        auto& tiles = gridHandler.RetrieveAllTiles();

        selectedTile = gridHandler.GetSelectedTile();     

        gridCurrentTile = selectedTile.GetPosition() / 50.f;

        // Velg spilleren, dersom ingen enheter har blitt valgt enda
        if (!isSelected && preventSelect && !inMenu && state == State::idle)
        {
            // Flytter musen til samme rute som spilleren
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                int roundedY = static_cast<int>(std::round(tileLocation.y));
                int roundedX = static_cast<int>(std::round(tileLocation.x));

                // Står spilleren på samme rute som er valgt på rutefeltet
                if (roundedY == gridCurrentTile.y && roundedX == gridCurrentTile.x)
                {
                    isSelected = true;
                    preventSelect = false;
                    algorithm.CreateRoute(tileLocation, movement, tiles);
                    state = State::selected;
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

    // Alle handlinger en karakter kan ta etter de har bevegd seg
    // Åpner menyen med "Attack", "Item", osv..
    void Player::MenuActions()
    {
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
                        state = State::attack;
                        animations->setPositions(gridCurrentTile);
                        SetTileToOccupied();
                        previousPosition = tileLocation;
                        tileLocation = gridCurrentTile;

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
        if (state == State::attack && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && tileLocation != gridHandler.GetSelectedTile().GetPosition() / 50.f)
        {
            selectedTile = gridHandler.GetSelectedTile();     
            gridCurrentTile = selectedTile.GetPosition() / 50.f;

            state = State::attacking; 
        }
        else if (state == State::attacking)
        {
            attackSpawnTimer--;

            std::cout << "\ntimer" << attackSpawnTimer;

            if (attackSpawnTimer <= 0)
            {
                Attack((gridCurrentTile * 50.f));
                inMenu = false;
            }

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

