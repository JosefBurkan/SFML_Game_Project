#include "UnitManager.hpp"

namespace UnitsManagers
{
    void UnitsManager::AddUnit(std::shared_ptr<Units::Unit> unit)
    {
        units.push_back(unit);
    }

    std::vector<std::shared_ptr<Units::Unit>> UnitsManager::GetAllUnits()
    {
        return units;
    }

    void UnitsManager::RemoveUnit()
    {
        units.clear();
    }

    std::pair<int, int> UnitsManager::GetCameraPositions(std::pair<int, int> cameraPos)
    {
        cameraPositions = cameraPos;
        return cameraPos;
    }   

    void UnitsManager::DrawUnit(std::shared_ptr<Units::Unit> it, sf::RenderWindow& window)
    {
        if (it->state != "Attacking")
        {
            it->Draw(window);
        }
        else 
        {
            it->DrawAttackAnimation(window);
        }
    }

    // Kjøres hver frame. Tegner animasjon, sjekker om uniten blir truffet, etc.
    void UnitsManager::UpdateUnits(sf::RenderWindow& window)
    {
        for (auto it = units.begin(); it != units.end(); ) 
        {
            float posX = (*it)->sprite->getPosition().x;
            float posY = (*it)->sprite->getPosition().y;

            HealthBars::HealthBar healthBar{posX, posY};

            DrawUnit((*it), window);

            (*it)->IsHit();

            if ((*it)->type == "Player")
            {
                (*it)->DrawUI(window);
            }
            else
            {
                healthBar.Draw(window, (*it)->healthPoints, (*it)->maxHealth);
            }

            if ((*it)->healthPoints == 0) {
                (*it)->SetTileToUnOccupied();
                it = units.erase(it);
                SortUnits(); 
            } else {
                ++it;
            }
        }
    }

    void UnitsManager::PerformEnemyActions(int gameTurn)
    {
        for (auto it = units.begin(); it != units.end(); ++it) 
        {
            if ((*it)->type == "Enemy" && (*it)->turn == gameTurn) 
            {
                (*it)->SetTileToUnOccupied();
                (*it)->PerformActions(); 
                (*it)->SetTileToOccupied();
            }
        }
    }

    void UnitsManager::SortUnits()
    {
        // Sorterer etter farten til units. Raske units går først
        std::sort(units.begin(), units.end(), [](const std::shared_ptr<Units::Unit>& a, const std::shared_ptr<Units::Unit>& b) {
            return a->speed > b->speed; 
        });

        assignTurn = 0;

        for (auto it = units.begin(); it != units.end(); ++it) 
        {
            (*it)->turn = assignTurn;
            (*it)->currentOrder = assignTurn;
            std::cout << (*it)->name << " speed: " << (*it)->speed << "\n";
            assignTurn++;
        }
        std::cout << "\n";
    }

    // Hent uniten som har lik index som runden
    // Første unit i lista vil da hentes på første turn, aka den raskeste uniten
    std::shared_ptr<Units::Unit> UnitsManager::GetUnitByTurn(int turn)
    {
        return units[turn];
    }

    // oppdater rekkefølgen til unitsa, basert på hvilken unit som har
    // utført en handling
    void UnitsManager::AssignOrder()
    {
        for (auto it = units.begin(); it != units.end(); ++it) 
        {
            if ((*it)->currentOrder > 0)
            {
                (*it)->currentOrder -= 1;
            }
        }
    }

    int UnitsManager::GetSize()
    {
        return units.size();
    }

}