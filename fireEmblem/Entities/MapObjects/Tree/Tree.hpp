#pragma once
#include "../MapObject.hpp"
#include "../../../config.hpp"
#include "../../../GridSystem/GridHandler/GridHandler.hpp"


namespace Trees
{
    class Tree : public MapObjects::MapObject
    {
        public:
            Tree(sf::Texture& texture);
            void SetTileToOccupied() override;

    };
}