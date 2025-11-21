#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Enemies/Enemy.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/Algorithms/EnemyPathAlgorithm/EnemyPathAlgorithm.hpp"


namespace Maps {
    class Map;
}

namespace Slimes
{
    class Slime : public Enemies::Enemy
    {
        private:
            EnemyPathAlgorithms::EnemyPathAlgorithm algorithm;
            std::pair<float, float> playerPos = {0, 0};

        public:
            Slime(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks, float yPos, float xPos);
            void Draw(sf::RenderWindow& window) override;
            void PerformActions() override;

    };
}