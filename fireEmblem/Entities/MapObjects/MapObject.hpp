#pragma once
#include "../../config.hpp"
#include "../../GridSystem/GridHandler/GridHandler.hpp"
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/GridSystem/GridMovement/GridMovement.hpp"

namespace MapObjects
{
    class MapObject
    {
        public:
        std::optional<sf::Sprite> sprite;
        std::string name = "Testobjekt ";
        GridHandlers::GridHandler* GridHandler = nullptr;
        
        MapObject(const sf::Texture& texture);
        sf::Sprite GenerateSprite();
        sf::Sprite& RetrieveSprite();
        std::pair<float, float> printPos();
        virtual void SetTileToOccupied();
        void Position(std::pair<float, float> position);
        void SetGrid(GridHandlers::GridHandler& grid);
        GridHandlers::GridHandler& FetchGrid();
        void Draw(sf::RenderWindow& window);
        // Transformer koordinater, til index
        std::pair<int, int> TransformPositionToIndex(float positionX, float positionY);
        
    };
}