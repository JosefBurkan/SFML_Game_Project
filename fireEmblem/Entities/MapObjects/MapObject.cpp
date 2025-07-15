#include "../../config.h"
using namespace GridGenerators;


namespace MapObjects
{
    class MapObject
    {
        public:
        sf::Texture texture;

        

        sf::Sprite GenerateSprite()
        {
            texture.loadFromFile("pixel-bat.png");
            sf::Sprite sprite(texture);
            sprite.setScale({0.1f, 0.1f});

            return sprite;
        }


    };
}