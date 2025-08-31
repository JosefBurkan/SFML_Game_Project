#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/config.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Enemies/Enemy.hpp"

namespace EnemyManagers
{
    // Klasse for å håndtere fiender. Altså ødelegge dem når de dør, 
    // sortere dem i lister og mer
    class EnemyManager
    {
        private:
            std::vector<std::shared_ptr<Enemies::Enemy>> enemies;       // Pointer for å sørge at fiendene ikke kopieres inn

        public:

            void AddEnemy(std::shared_ptr<Enemies::Enemy> enemy);
            std::vector<std::shared_ptr<Enemies::Enemy>> AllEnemies();
            void RemoveEnemy();
            void UpdateEnemies(sf::RenderWindow& window);
    };
}