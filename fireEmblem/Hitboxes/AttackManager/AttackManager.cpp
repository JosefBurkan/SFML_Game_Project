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
            attack->Draw(window);
        }
    }

    void AttackManager::CreateAttack(float positionX, float positionY)
    {
        activeAttacks.push_back(std::make_unique<Attacks::Attack>(positionX, positionY));
        attackLife = 0;
    }

    void AttackManager::CreateRangedAttack(float positionX, float positionY, std::pair<int, int> directions)
    {
        activeAttacks.push_back(std::make_unique<RangedAttacks::RangedAttack>(positionX, positionY, directions));
        attackLife = 0;
    }

    void AttackManager::Update()
    {
        attackLife++;

        for (auto& attacks : activeAttacks)
        {
            if (attackLife >= 20)
            {
                activeAttacks.clear();
            }
        }
    }

    void AttackManager::Clear()
    {
        activeAttacks.clear();
    }
}
