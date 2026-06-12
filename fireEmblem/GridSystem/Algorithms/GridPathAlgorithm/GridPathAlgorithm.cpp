#include "GridPathAlgorithm.hpp"

namespace GridPathAlgorithms
{
    // Farg de rutene som spilleren kan bevege seg til
    void GridPathAlgorithm::CreateRoute(sf::Vector2f start, int range, std::vector<std::vector<Tiles::Tile>>& tiles)
    {

        std::queue<std::tuple<int, int, int>> q;        // For å vite hvilken rute som skal utforskes neste tikk
        std::set<std::pair<int, int>> visited;          // Hvilke ruter er besøkt
        std::vector<std::pair<int, int>> directions = {{1,0},{-1,0},{0,1},{0,-1}}; // Ned, opp, høyre, venstre

        int startY = start.x;
        int startX = start.y;

        visited.insert({startY / 50, startX / 50});
        q.push({startY / 50, startX / 50, 0});

        while (!q.empty())
        {
            auto [y, x, cost] = q.front();
            q.pop();

            // Dersom g er større enn bevegelseshastigheten til spilleren, hopp over
            if (cost > range)
            {
                continue;
            }

            for (auto [dy,dx] : directions)
            {
                int nx = x + dx;
                int ny = y + dy;

                // Ikke beveg utenfor banen
                if (nx < 0 || ny < 0 || ny >= tiles.size() || nx >= tiles[0].size()) continue;
                // Ikke beveg på okkuperte ruter
                if (tiles[ny][nx].IsOccupied) continue;
                if (tiles[ny][nx].IsOccupiedByPlayer) continue;

                if (visited.count({ny,nx})) continue;

                tiles[startY / 50][startX / 50].inRange = true;
                tiles[ny][nx].inRange = true;

                visited.insert({ny, nx});

                q.push({ny, nx, cost+1});

                tiles[ny][nx].MarkPath();
            }
        }
    }

    // Fjern de fargete rutene etter en spiller flytter seg
    void GridPathAlgorithm::CleanGrid(std::vector<std::vector<Tiles::Tile>>& tiles)
    {
        for (auto& tile : tiles)
        {
            for (auto& t : tile)
            {
                t.inRange = false;
                t.parent = nullptr;
            }
        }
    }
}
