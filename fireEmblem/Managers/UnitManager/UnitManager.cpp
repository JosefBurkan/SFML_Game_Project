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
        if (it->state == "Attacking")
        {
            it->DrawAttackAnimation(window);
        }
        else if (it->state == "Dying")
        {
            it->DrawDeathAnimation(window);
        }
        else 
        {
            it->Draw(window);
            it->ResetAttackAnimation();
        }
    }

    // Kjøres hver frame. Tegner animasjon, sjekker om uniten blir truffet, etc.
    void UnitsManager::UpdateUnits(sf::RenderWindow& window)
    {
        // For å sørge for at ingen fiender hoppes over
        // når listen sorters
        bool needsSorting = false; 

        for (auto it = units.begin(); it != units.end(); ) 
        {
            float posX = (*it)->sprite->getPosition().x;
            float posY = (*it)->sprite->getPosition().y;

            HealthBars::HealthBar healthBar{posX, posY};

            // Hvis uniten blir truffet, sjekk hvem som traff den
            if ((*it)->IsHit())
            {
                std::string lastHitBy = (*it)->LastHitBy();

                // Finn uniten den selv ble drept av
                auto hitIt = std::find_if(units.begin(), units.end(),
                    [&lastHitBy](const auto& unit) { return unit->name == lastHitBy; });

            }

            if ((*it)->type == "Player")
            {
                (*it)->DrawUI(window);
            }
            else
            {
                healthBar.Draw(window, (*it)->currentHealth, (*it)->maxHealth);
            }

            if ((*it)->currentHealth <= 0) 
            {
                (*it)->deathAnimationTimer--;

                (*it)->state = "Dying";

                if ((*it)->deathAnimationTimer <= 0)
                {
                    std::string lastHitBy = (*it)->LastHitBy();

                    // Finn uniten den selv ble drept av
                    auto hitIt = std::find_if(units.begin(), units.end(),
                        [&lastHitBy](const auto& unit) { return unit->name == lastHitBy; });

                    // Gi den uniten XP
                    if (hitIt != units.end())
                    {
                        (*hitIt)->RecieveExperience((*it)->GrantExperience());
                    }

                    (*it)->SetTileToUnOccupied();
                    it = units.erase(it);
                    needsSorting = true;
                    continue; // Kjør løkken igjen med en gang. Unngår en bug ved tegning av karakter på drap.
                }
            }

            (*it)->CheckForLevelUp();

            DrawUnit((*it), window);

            ++it;
        }

        if (needsSorting)
        {
            SortUnits();
        }
    }


    void UnitsManager::LoadUnits()
    {
        for (auto it = units.begin(); it != units.end(); ++it) 
        {
            (*it)->ReadData();
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
            assignTurn++;
        }
    }

    // Hent uniten som har lik index som runden
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
                (*it)->currentOrder--;
            }
        }
    }

    int UnitsManager::GetSize()
    {
        return units.size();
    }

}
