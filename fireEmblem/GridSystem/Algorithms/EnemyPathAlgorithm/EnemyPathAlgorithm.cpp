#include "EnemyPathAlgorithm.hpp"

namespace EnemyPathAlgorithms
{
    // Farg de rutene som spilleren kan bevege seg til
    std::vector<Tiles::Tile> EnemyPathAlgorithm::CheckAvailableTiles(int startY, int startX, int range, std::vector<std::vector<Tiles::Tile>>& tiles)
    {

        // Først rens alle ruter sine parentpekere, ellers kan det kræsje
        for (auto& row : tiles)
        {
            for (auto& tile : row)
            {
                tile.parent = nullptr;
            }
        }

        // startX, statY, avstandReist
        std::queue<std::tuple<int, int, int>> q;        // For å vite hvilken rute som skal utforskes neste tikk
        std::queue<std::pair<int, int>> traceBack;       // For å spore veien tilbake etter målet er nådd

        std::set<std::pair<int, int>> visited;          // Hvilke ruter er besøkt

        // Ned, opp, høyre, venstre
        std::vector<std::pair<int, int>> directions = {{1,0},{-1,0},{0,1},{0,-1}};

        visited.insert({startY, startX});
        q.push({startY, startX, travelCost});

        while (!q.empty())
        {
            auto [y, x, tilesTraveled] = q.front();
            q.pop();

            if (tilesTraveled > range)
                continue;

            for (auto [dirY, dirX] : directions)
            {
                int nextX = x + dirX;
                int nextY = y + dirY;

                if (nextX < 0 || nextY < 0 ||
                    nextY >= tiles.size() || nextX >= tiles[0].size())
                    continue;

                if (tiles[nextY][nextX].IsOccupied)
                    continue;

                if (visited.count({nextY, nextX}))
                    continue;

                visited.insert({nextY, nextX});

                tiles[nextY][nextX].parent = &tiles[y][x];


                if (tiles[nextY][nextX].IsOccupiedByPlayer)
                {
                    playerDetected = true;
                    return TracePath(&tiles[nextY][nextX]);
                }

                q.push({nextY, nextX, tilesTraveled + 1});
            }
        }

        playerDetected = false;


        return {};
    }

    // Spor veien tilbake
    std::vector<Tiles::Tile> EnemyPathAlgorithm::TracePath(Tiles::Tile* goal)
    {
        
        std::vector<Tiles::Tile> path;

        Tiles::Tile* current = goal;

        while (current != nullptr)
        {
            path.push_back(*current);
            current = current->parent;
        }

        return path;
    }

}
