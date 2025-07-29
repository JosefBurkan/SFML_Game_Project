#pragma once
#include "../../../config.hpp"

namespace BackgroundTiles 
{
    class BackgroundTile
    {
        public:
        sf::Texture texture;
        std::optional<sf::Sprite> sprite;
        int tileLocationX = 0;               // Avgjør hvilken del av tilsettet som skal bli brukt
        int tileLocationY = 0;

        BackgroundTile();

        void Draw(sf::RenderWindow& window);
        void ChangeTile(int tileID);

    };

}
