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

    void AttackManager::CreateAttack(std::string source, int atkValue, sf::Vector2f position)
    {
        activeAttacks.push_back(std::make_unique<Attacks::Attack>(source, atkValue, position));
        attackLife = 0;
    }

    void AttackManager::CreateRangedAttack(std::string source, int atkValue, sf::Vector2f position, std::pair<int, int> directions)
    {
        activeAttacks.push_back(std::make_unique<RangedAttacks::RangedAttack>(source, atkValue, position, directions));
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
