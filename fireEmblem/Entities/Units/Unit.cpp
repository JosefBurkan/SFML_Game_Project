#include "Unit.hpp"

namespace Units 
{
    // spritePath er for å kunne sette sprites til enheter når de opprettes
    Unit::Unit(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks) 
            : gridGenerator(gridReference), map(map), attacks(attacks)
    {

    }
    
    void Unit::spawn()
    {
        std::cout << "spawnet! \n";
    }
    
    std::pair<int, int> Unit::RetriveCoordinations() 
    {

    }

    void Unit::Draw(sf::RenderWindow& window) 
    {
        window.draw(*sprite);
    }

        // Sjekk hvilket baneobjekt spilleren står på, feks. skog
    void Unit::CheckForMapObjects()
    {
        for (auto& object : map.mapObjects)
        {
            if (sprite->getPosition().x == object.printPos().first + 10 && sprite->getPosition().y == object.printPos().second)
            {
                std::cout << "Nå står du på: " << object.name << "\n";
            }
        }
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
}

