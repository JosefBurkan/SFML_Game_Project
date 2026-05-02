#include "EnemyPathAlgorithm.hpp"

namespace EnemyPathAlgorithms
{
    // Farg de rutene som spilleren kan bevege seg til
    std::pair<float, float> EnemyPathAlgorithm::CheckAvailableTiles(int startY, int startX, int range, std::vector<std::vector<Tiles::Tile>>& tiles)
    {
        // startX, statY, avstandReist
        std::queue<std::tuple<int, int, int>> q;        // For å vite hvilken rute som skal utforskes neste tikk
        std::set<std::pair<int, int>> visited;          // Hvilke ruter er besøkt
        // Ned, opp, høyre, venstre
        std::vector<std::pair<int, int>> directions = {{1,0},{-1,0},{0,1},{0,-1}};

        visited.insert({startY, startX});
        q.push({startY, startX, travelCost});

        while (!q.empty())
        {
            auto [y, x, tilesTraveled] = q.front();
            q.pop();
   
            // Dersom g er større enn bevegelseshastigheten til spilleren, hopp over
            if (tilesTraveled > range) continue;

            for (auto [dirY,dirX] : directions)
            {
                int nextX = x + dirX;
                int nextY = y + dirY;

                // Ikke beveg utenfor banen
                if (nextX < 0 || nextY < 0 || nextY >= tiles.size() || nextX >= tiles[0].size()) continue;

                // Ikke beveg på okkuperte ruter
                if (tiles[nextY][nextX].IsOccupied) continue;

                if (tiles[nextY][nextX].IsOccupiedByPlayer)
                {
                    playerDetected = true;
                    return {nextY, nextX};
                }

                if (visited.count({nextY,nextX})) continue;

                q.push({nextY, nextX, tilesTraveled + 1});
                visited.insert({nextY, nextX});
                
            }
        }
        playerDetected = false;
        return {startY, startX};
    }
}
