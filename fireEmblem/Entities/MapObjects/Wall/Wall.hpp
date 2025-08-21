#pragma once
#include "../MapObject.hpp"
#include "../../../config.hpp"
#include "../../../GridSystem/GridMovement/GridMovement.hpp"


namespace Walls
{
    class Wall : public MapObjects::MapObject
    {
        public:
            Wall(const sf::Texture& texture);

    };
}