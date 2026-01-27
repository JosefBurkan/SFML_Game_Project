#include "EnemyPathAlgorithm.hpp"

namespace EnemyPathAlgorithms
{
    // Farg de rutene som spilleren kan bevege seg til
    std::pair<float, float> EnemyPathAlgorithm::CheckAvailableTiles(int startY, int startX, int range, std::vector<std::vector<Tiles::Tile>>& tiles)
    {
        coordinateY = startY;
        coordinateX = startX;
        // startX, statY, avstandReist
        std::queue<std::tuple<int, int, int>> q;        // For å vite hvilken rute som skal utforskes neste tikk
        std::set<std::pair<int, int>> visited;          // Hvilke ruter er besøkt
        // Ned, opp, høyre, venstre
        std::vector<std::pair<int, int>> directions = {{1,0},{-1,0},{0,1},{0,-1}};

        tiles[startY][startX].MarkAttackRange();

        visited.insert({startY, startX});
        q.push({startY, startX, 0});

        while (!q.empty())
        {
            auto [y, x, g] = q.front();
            q.pop();

            // Dersom g er større enn bevegelseshastigheten til spilleren, hopp over
            if (g > range) continue;

            for (auto [dy,dx] : directions)
            {
                int nx = x + dx;
                int ny = y + dy;

                // Ikke beveg utenfor banen
                if (nx < 0 || ny < 0 || ny >= tiles.size() || nx >= tiles[0].size()) continue;

                // Ikke beveg på okkuperte ruter
                if (tiles[ny][nx].IsOccupied) continue;

                if (tiles[ny][nx].IsOccupiedByPlayer)
                {
                    // std::cout << startY << startX;
                    playerDetected = true;
                    return {ny, nx};
                }

                if (visited.count({ny,nx})) continue;

                q.push({ny, nx, g+1});
                visited.insert({ny, nx});
            }

        }
        playerDetected = false;
        return {startY, startX};
    }
}
