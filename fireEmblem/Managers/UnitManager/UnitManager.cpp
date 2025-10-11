#include "UnitManager.hpp"

namespace UnitsManagers
{
    void UnitsManager::AddUnit(std::shared_ptr<Units::Unit> unit)
    {
        units.push_back(unit);
    }

    std::vector<std::shared_ptr<Units::Unit>> UnitsManager::AllUnits()
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
            } else {
                ++it;
            }
        }
    }

    // Perform actions automatically, only if the unit is an enemy
    void UnitsManager::PerformEnemyActions()
    {
        for (auto it = units.begin(); it != units.end(); ++it) 
        {
            if ((*it)->type == "Enemy") {
                (*it)->PerformActions(); 
            }
        }
    }

}