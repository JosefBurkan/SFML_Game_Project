#include "AttackManager.hpp"

namespace AttackManagers
{
    AttackManager::AttackManager()
    {

    }

    void AttackManager::Draw(sf::RenderWindow& window)
    {

        for (auto& attack : activeAttacks)
        {
            attack.Draw(window);
        }

    }

    void AttackManager::CreateAttack(Attacks::Attack newAttack)
    {
        activeAttacks.push_back(newAttack);
        attackLife = 0;
    }

    void AttackManager::Update()
    {
        attackLife++;

        for (auto& attacks : activeAttacks)
        {
            if (attackLife >= 1)
            {
                activeAttacks.clear();
            }
        }

    }



}
