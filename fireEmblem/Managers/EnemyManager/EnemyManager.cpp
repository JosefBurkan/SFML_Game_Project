#include "EnemyManager.hpp"

namespace EnemyManagers
{
    void EnemyManager::AddEnemy(std::shared_ptr<Enemies::Enemy> enemy)
    {
        enemies.push_back(enemy);
    }

    std::vector<std::shared_ptr<Enemies::Enemy>> EnemyManager::AllEnemies()
    {
        return enemies;
    }

    void EnemyManager::RemoveEnemy()
    {
        enemies.clear();
    }

    void EnemyManager::UpdateEnemies(sf::RenderWindow& window)
    {
        for (auto& enemy : enemies)
        {
            enemy->Draw(window);
            enemy->IsHit();

            if (enemy->healthPoints == 0)
            {
                enemies.clear();
            }
        }
    }

}