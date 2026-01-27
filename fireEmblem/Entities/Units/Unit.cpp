#include "Unit.hpp"

namespace Units 
{
    // spritePath er for å kunne sette sprites til enheter når de opprettes
    Unit::Unit(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks) 
            : gridGenerator(gridReference), map(map), attacks(attacks)
    {
        defaultTexture.setSmooth(false);

        int randomNum = rand() % 4;

        framesUntilDraw = (randomNum * 3) - 1;
        
        std::cout << framesUntilDraw << "\n";

        sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));
        attackSprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));

        iconTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/prinsesse_Icon.png");

    }
    
    void Unit::spawn()
    {
        std::cout << "spawnet! \n";
    }
    
    std::pair<int, int> Unit::RetriveCoordinations() 
    {

    }

    void Unit::ResetAnimations()
    {
        defaultTextureX = 0;
        defaultTextureY = 0;

        attackingTextureX = 0;
        attackingTextureY = 0;

        attackSpawnTimer = 16;
    }

    void Unit::Draw(sf::RenderWindow& window) 
    {
        framesUntilDraw++;
        spriteSizeY = 50;
        drawSpeed = 20;
            
        if (framesUntilDraw >= drawSpeed)
        {
            while (defaultTextureX >= spriteSizeX)
            {
                defaultTextureY += 50;
                defaultTextureX = 0;

                if (defaultTextureY > spriteSizeY)
                {
                    defaultTextureY = 0;
                }
            }

            sprite->setTextureRect(sf::IntRect({defaultTextureX, defaultTextureY}, {50, 50}));

            defaultTextureX += 50;
            framesUntilDraw = 0;
        }

        window.draw(*sprite);
    }

    void Unit::DrawAttackAnimation(sf::RenderWindow& window)
    {
        framesUntilDraw++;

        spriteSizeY = 100;
        drawSpeed = 5;

        if (framesUntilDraw >= drawSpeed)
        {
            while (attackingTextureX >= spriteSizeX)
            {
                attackingTextureY += 50;
                attackingTextureX = 0;

                if (attackingTextureY > spriteSizeY)
                {
                    attackingTextureY = 0;
                }
            }

            attackSprite->setTextureRect(sf::IntRect({attackingTextureX, attackingTextureY}, {50, 50}));

            attackingTextureX += 50;
            framesUntilDraw = 0;
        }

        window.draw(*attackSprite);
    }

    void Unit::DrawUI(sf::RenderWindow& window)
    {

    }

    // Sjekk hvilket baneobjekt spilleren står på, feks. skog
    // Sjekker kun trær nå, og de kan ikke tråkkes på uansett.
    // Skal ha en felles mappe med alle objekter som er mulige å tråkke på
    void Unit::CheckForMapObjects()
    {
        for (auto& object : map.trees)
        {
            if (sprite->getPosition().x == object.printPos().first + 10 && sprite->getPosition().y == object.printPos().second)
            {
                std::cout << "Nå står du på: " << object.name << "\n";
            }
        }
    }

    void Unit::Move(float posX, float posY)
    {
        sprite->setPosition({posX, posY});
    }

    void Unit::Movement()
    {

    }

    void Unit::IsHit()
    {
        // Hent uniten sin posisjon for sammenligning
        int x = sprite->getPosition().x;
        int y = sprite->getPosition().y;
        
        // Sjekk eksisterende angrep
        for (auto& attack : attacks.activeAttacks)
        {
            // Hent posisjonen til de angrepene
            int atkx = attack.hitbox.getPosition().x;
            int atky = attack.hitbox.getPosition().y;

            // Hvis spilleren sin posisjon er større eller lik angrepet sitt
            if (x >= atkx - 5 && y >= atky - 5)
            {
                // splleren sin posisjon er mindre eller lik angrepet + ruten sin størrelse
                if (x <= atkx + tileSize - 10 && y <= atky + tileSize - 10)
                {
                    healthPoints--;
                    std::cout << name << " er truffet! " << healthPoints << "\n";
                }
            }
        }
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

    }

    void Unit::SetTileToUnOccupied()
    {

    }
}

