#include "PlayerPathAlgorithm.hpp"

namespace PlayerPathAlgorithms
{
    // Farg de rutene som spilleren kan bevege seg til
    std::vector<Tiles::Tile> PlayerPathAlgorithm::CheckAvailableTiles(int startY, int startX, std::vector<std::vector<Tiles::Tile>>& tiles)
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

        std::set<std::pair<int, int>> visited;          // Hvilke ruter er besøkt

        // Ned, opp, høyre, venstre
        std::vector<std::pair<int, int>> directions = {{1,0},{-1,0},{0,1},{0,-1}};

        visited.insert({startY, startX});
        q.push({startY, startX, travelCost});


        while (!q.empty())
        {
            auto [y, x, tilesTraveled] = q.front();
            q.pop();

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

                tiles[nextY][nextX].MarkAttackRange();


                if (tiles[nextY][nextX].IsOccupiedByPlayer)
                {
                    playerDetected = true;
                    return TracePath(&tiles[nextY][nextX]);
                }

                q.push({nextY, nextX, tilesTraveled + 1});
            }
        }

        playerDetected = false;
        std::cout << "Spiller Ikke oppdaget: ";
        return {};
    }

    // Spor veien tilbake ved å se på hver tile sin parent
    std::vector<Tiles::Tile> PlayerPathAlgorithm::TracePath(Tiles::Tile* goal)
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
