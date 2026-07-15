#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Enemies/Enemy.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Sprites/SlimeSprite/SlimeSprite.hpp"
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

            std::vector<Tiles::Tile> path;

            float nextTileY = 0;
            float nextTileX = 0;


            int cooldown = 0;

        public:
            SlimeSprites::SlimeSprite slimeAnimations;

            Slime(GridHandlers::GridHandler& gridHandler, AttackManagers::AttackManager& attacks, float yPos, float xPos);
            void PerformActions() override;
            void SetPathToPlayer() override;             // Kjør algorithmen som scanner etter spiller og lager vei
            void Movement() override;

    };
}