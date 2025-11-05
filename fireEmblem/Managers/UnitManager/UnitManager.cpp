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

    void UnitsManager::UpdateUnits(sf::RenderWindow& window)
    {
        for (auto it = units.begin(); it != units.end(); ) 
        {
            (*it)->Draw(window);
            (*it)->IsHit();

            if ((*it)->healthPoints == 0) {
                it = units.erase(it);
                SortUnits(); 
            } else {
                ++it;
            }
        }
    }

    // Endre dette til å ta inn en int (turn) som argument
    // Endre til å gjelde for alle units, ikke bare fiender
    // 
    void UnitsManager::PerformEnemyActions(int gameTurn)
    {
        for (auto it = units.begin(); it != units.end(); ++it) 
        {
            if ((*it)->type == "Enemy" && (*it)->turn == gameTurn) 
            {
                (*it)->PerformActions(); 
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


    int UnitsManager::GetSize()
    {
        return units.size();
    }

}