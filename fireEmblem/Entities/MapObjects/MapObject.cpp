#include "MapObject.hpp"

namespace MapObjects
{

    MapObject::MapObject()
    {
        texture.loadFromFile("pixel-bat.png");
        sprite.emplace(texture);
        sprite->setScale({0.1f, 0.1f});
    }

    sf::Sprite& MapObject::RetrieveSprite() 
    {
        return *sprite;
    }

    std::pair<float, float> MapObject::printPos()
    {
        return {sprite->getPosition().x, sprite->getPosition().y};
    }



}