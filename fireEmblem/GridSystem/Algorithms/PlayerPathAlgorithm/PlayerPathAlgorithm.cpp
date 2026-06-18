#include "PlayerPathAlgorithm.hpp"

namespace PlayerPathAlgorithms
{
    // Farg de rutene som spilleren kan bevege seg til
    std::vector<Tiles::Tile> PlayerPathAlgorithm::CheckAvailableTiles(sf::Vector2f start, std::vector<std::vector<Tiles::Tile>>& tiles)
    {

        // Først rens alle ruter sine parentpekere, ellers kan det kræsje
        for (auto& row : tiles)
        {
            for (auto& tile : row)
            {
                tile.parent = nullptr;
            }
        }

        std::pair<int, int> startPair = {start.y / 50, start.x / 50};

        // startX, statY, avstandReist
        std::queue<std::tuple<std::pair<int, int>, int>> q;        // For å vite hvilken rute som skal utforskes neste tikk

        std::set<std::pair<int, int>> visited;          // Hvilke ruter er besøkt

        // Ned, opp, høyre, venstre
        std::vector<sf::Vector2f> directions = {{1,0},{-1,0},{0,1},{0,-1}};

        visited.insert(startPair);
        q.push({startPair, travelCost});


        while (!q.empty())
        {
            auto [pos, tilesTraveled] = q.front();
            q.pop();

            for (auto [dirY, dirX] : directions)
            {
                std::pair<int, int> next = {0, 0};
                
                next.first = pos.first + dirY;
                next.second = pos.second + dirX;

                if (next.first < 0 || next.second < 0 ||
                    next.first >= tiles.size() || next.second >= tiles[0].size())
                    continue;

                if (tiles[next.first][next.second].IsOccupied)
                    continue;

                if (tiles[next.first][next.second].unit != nullptr)
                    continue;

                if (visited.count(next))
                    continue;

                visited.insert(next);

                tiles[next.first][next.second].parent = &tiles[pos.first][pos.second];

                if (tiles[next.first][next.second].isSelected)
                {
                    playerDetected = true;
                    return TracePath(&tiles[next.first][next.second]);
                }

                q.push({next, tilesTraveled + 1});

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
