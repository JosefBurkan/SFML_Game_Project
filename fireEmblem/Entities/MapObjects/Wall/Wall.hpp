#pragma once
#include "../MapObject.hpp"
#include "../../../GridSystem/GridHandler/GridHandler.hpp"


namespace Walls
{
    class Wall : public MapObjects::MapObject
    {
        public:
            Wall(sf::Texture& texture);

    };
}