#include "GridPathAlgorithm.hpp"

namespace GridPathAlgorithms
{
    // Farg de rutene som spilleren kan bevege seg til
    void GridPathAlgorithm::CheckAvailableTiles(int startY, int startX, int range, std::vector<std::vector<Tiles::Tile>>& tiles)
    {
        // Divider på 50 for å finne index
        coordinateY = startY / 50;
        coordinateX = startX / 50;
        // startX, statY, avstandReist
        std::queue<std::tuple<int, int, int>> q;        // For å vite hvilken rute som skal utforskes neste tikk
        std::set<std::pair<int, int>> visited;          // Hvilke ruter er besøkt
        // Ned, opp, høyre, venstre
        std::vector<std::pair<int, int>> directions = {{1,0},{-1,0},{0,1},{0,-1}};

        visited.insert({coordinateY, coordinateX});
        q.push({coordinateY, coordinateX, 0});

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

                tiles[coordinateY][coordinateX].inRange = true;
                if (g < range) tiles[ny][nx].inRange = true;

                if (visited.count({ny,nx})) continue;

                q.push({ny, nx, g+1});
                visited.insert({ny, nx});

                if (g < range) tiles[ny][nx].MarkPath();
            }
        }
    }

    // Fjern de fargete rutene etter en spiller flytter seg
    void GridPathAlgorithm::CleanGrid(std::vector<std::vector<Tiles::Tile>>& tiles, float gridCurrentTileY, float gridCurrentTileX)
    {
        for (auto& tile : tiles)
        {
            

            for (auto& t : tile)
            {
                // Ikke fjern ruta som spilleren står på
                if (t.RetrieveTilePos().first == gridCurrentTileX &&
                    t.RetrieveTilePos().second == gridCurrentTileY)
                {

                }
                else
                {
                    t.UnMark();
                    t.inRange = false;
                }
            }
        }
    }
}
