#include "GridPathAlgorithm.hpp"

namespace GridPathAlgorithms

{

    void GridPathAlgorithm::CheckAvailableTiles(int startX, int startY, int range, std::vector<std::vector<Tiles::Tile>>& tiles)
    {
        // startX, statY, avstandReist
        std::queue<std::tuple<int, int, int>> q;        // For å vite hvilken rute som skal utforskes neste tikk
        std::set<std::pair<int, int>> visited;          // Hvilke ruter er besøkt
        // Ned, opp, høyre, venstre
        std::vector<std::pair<int, int>> directions = {{1,0},{-1,0},{0,1},{0,-1}};

        visited.insert({startY, startX});
        q.push({startY, startX, 0});

        while (!q.empty())
        {
            auto [x, y, g] = q.front();
            q.pop();

            // Dersom g er større enn bevegelseshastigheten til spilleren, hopp over
            if (g > range) continue;
            for (auto [dx,dy] : directions)
            {
                int nx = x + dx;
                int ny = y + dy;

                // Ikke beveg utenfor banen
                if (nx < 0 || ny < 0 || nx >= tiles.size() || ny >= tiles[0].size()) continue;
                // Ikke beveg på okkuperte ruter
                if (tiles[nx][ny].IsOccupied) continue;

                tiles[startX][startY].inRange = true;
                tiles[nx][ny].inRange = true;

                if (visited.count({nx,ny})) continue;

                if (g < range) tiles[nx][ny].MarkPath();
                else if (g == range) tiles[nx][ny].MarkAttackRange();

                q.push({nx, ny, g+1});
                visited.insert({nx, ny});


            }
        }


    }

    void GridPathAlgorithm::CleanGrid(std::vector<std::vector<Tiles::Tile>>& tiles)
    {
        for (auto& tile : tiles)
        {
            for (auto& t : tile)
            {
                t.UnSelect();
                t.inRange = false;
            }
        }
    }
}
