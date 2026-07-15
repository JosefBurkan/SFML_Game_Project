#include "Unit.hpp"

namespace Units 
{
    // spritePath er for å kunne sette sprites til enheter når de opprettes map
    Unit::Unit(GridHandlers::GridHandler& gridHandler, AttackManagers::AttackManager& attacks) 
            : gridHandler(gridHandler), attacks(attacks)
    {
        int randomNum = rand() % 4;

        if (!iconTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/prinsesse_Icon.png"))
        {
            throw ("File not found");
        }

        if (!iconTextureLarge.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/prinsesse_Icon.png"))
        {
            throw ("File not found ");
        }

        state = State::idle;

        animations = nullptr;   // Gjør til null slik at de andre units kan sette spriten

    }
    
    sf::Vector2f Unit::GetPosition() 
    {
        return tileLocation;
    }

    // For tallet som kommer over uniten når de blir skadet
    void Unit::SetDamageNumber(std::string damageTaken)
    {
        damageNumber.PrepareDraw(damageTaken, animations->getIdlePosition());
    }

    void Unit::DrawDamageNumber(sf::RenderWindow& window)
    {
        damageNumber.Draw(window);
    }

    void Unit::Draw(sf::RenderWindow& window) 
    {
        animations->play(window, this);
    }

    void Unit::DrawLevelUpAnmiation (sf::RenderWindow& window)
    {

    }

    void Unit::DrawHealthBar(sf::RenderWindow& window)
    {
        healthBar.SetPosition(animations->getIdlePosition());
        healthBar.Draw(window, currentHealth, maxHealth);
    }

    void Unit::DrawUI(sf::RenderWindow& window)
    {

    }

    // Sjekk hvilket baneobjekt spilleren står på, feks. sand
    void Unit::CheckForMapObjects()
    {
      // Bytte til pointerløsning
    }

    void Unit::Place(float posX, float posY)
    {
        tileLocation = {posX / 50, posY / 50};
        animations->setPositions(tileLocation);
    }

    void Unit::Movement()
    {

    }

    void Unit::MenuActions()
    {

    }

    void Unit::SmoothMove()
    {

    }

    void Unit::ReverseSprite(int movementX, int movementY)
    {
        
        if (movementX == 5)
        {
            // movingSprite->setOrigin({0.f, 0.f}); 
            // movingSprite->setScale({1, 1});
        }
        else if (movementX == -5 && !finishedMoving)
        {
            // movingSprite->setOrigin({50.f, 0.f}); 
            // movingSprite->setScale({-1, 1});
        }
    }

    bool Unit::IsHit()
    {
        // Hent uniten sin posisjon for sammenligning
        int x = animations->getIdlePosition().x;
        int y = animations->getIdlePosition().y;
        
        // Sjekk eksisterende angrep
        for (auto& attack : attacks.activeAttacks)
        {
            // Hent posisjonen til de angrepene
            int atkx = attack->hitbox.getPosition().x;
            int atky = attack->hitbox.getPosition().y;

            // Hvis spilleren sin posisjon er større eller lik angrepet sitt
            if (x >= atkx - 5 && y >= atky - 5)
            {
                // uniten sin posisjon er mindre eller lik angrepet + ruten sin størrelse
                if (x <= atkx + tileSize - 10 && y <= atky + tileSize - 10)
                {
                    std::cout << name << " er truffet! " << currentHealth << "\n";

                    lastHitBy = attack->GetSource();
                    int damageToBeTaken = attack->GetValue();

                    currentHealth -= damageToBeTaken;

                    attacks.Clear();

                    if (currentHealth <= 0)
                    {
                        state = State::dying;
                    }

                    // Kan føre til bugs senere med angrep som kan treffe flere fiender.
                    return true;
                }
            }
        }

        return false;
    }

    void Unit::PerformActions()
    {
        
    }

    sf::Sprite Unit::GetIcon()
    {
        sf::Sprite iconSprite(iconTexture);
        return iconSprite;
    }

    void Unit::SetTileToOccupied()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();
        tiles[tileLocation.y][tileLocation.x].IsOccupied = true;
    }

    void Unit::SetTileToUnOccupied()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();
        tiles[tileLocation.y][tileLocation.x].RemoveUnit();
    }

    void Unit::setTileUnit()
    {
        auto& tiles = gridHandler.RetrieveAllTiles();
        tiles[tileLocation.y][tileLocation.x].unit = this;

    }

    void Unit::Attack(sf::Vector2f position)
    {

    }

    std::string Unit::LastHitBy()
    {
        return lastHitBy;
    }

    void Unit::RecieveExperience(int exp)
    {
        experience += exp;
    }

    int Unit::GrantExperience()
    {
        return experienceToGrant;
    }

    int Unit::GetExperience()
    {
        return experience;
    }

    bool Unit::CheckForLevelUp()
    {
        if (experience >= experienceToLevelUp)
        {
            experience = 0;
            level++;
            experienceToLevelUp *= level;

            std::cout << "Leveled up! ";
            return true;
        }

        return false;
    }

    void Unit::SaveData()
    {
        // Lagre data her
    }    
    void Unit::ReadData()
    {   
        // Lese data her
    }
    void Unit::SetData(std::array<int, 6> stats)
    {
        // Sette data her
    }

    void  Unit::SetPathToPlayer()
    {
        
    }
}

