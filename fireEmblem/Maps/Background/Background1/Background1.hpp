#pragma once
#include "../../../config.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/GridHandler/GridHandler.hpp"

namespace Backgrounds1
{
    class Background1 : public sf::Drawable, public sf::Transformable
    {
        public:
            GridHandlers::GridHandler& movement;
            sf::VertexArray m_vertices;
            sf::Texture     m_tileset;

            int tileWidt = 10;
            int tileHeight = 10;
            int columns = 20; // For å unngå segmentation fault i ReadTileFile
            sf::Vector2u tileSize = {50, 50};   // Bredde, høyde

            Background1(GridHandlers::GridHandler& GridHandler);
            bool LoadTileMapFromFile();
            void ReadTileFile();
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    };

}
