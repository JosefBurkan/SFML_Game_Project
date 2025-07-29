#include "BackgroundTile.hpp"

namespace BackgroundTiles
{
    BackgroundTile::BackgroundTile()
    {
        texture.loadFromFile("Tileset.png");
        sprite.emplace(texture);
        sprite->setTextureRect(sf::IntRect({0, 0}, {17, 17}));
        sprite->setScale({3.f, 3.f});
    }

    void BackgroundTile::Draw(sf::RenderWindow& window)
    {
        window.draw(*sprite);

    }

    void BackgroundTile::ChangeTile(int tileID)
    {
        tileLocationX = tileID * 16;
        tileLocationY = 0;

        while (tileLocationX >= 48)
        {
            tileLocationY += 16;
            tileLocationX -= 48;
        }

        sprite->setTextureRect(sf::IntRect({tileLocationX, tileLocationY}, {17, 17}));
    }
}