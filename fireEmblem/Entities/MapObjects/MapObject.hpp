#pragma once
#include "../../config.hpp"
#include "../../GridSystem/GridHandler/GridHandler.hpp"

namespace MapObjects
{
    class MapObject
    {
        public:
        sf::Texture texture;
        std::optional<sf::Sprite> sprite;
        std::string name = "Testobjekt ";
        GridHandlers::GridHandler* GridHandler = nullptr;
        
        MapObject();
        sf::Sprite GenerateSprite();
        sf::Sprite& RetrieveSprite();
        std::pair<float, float> printPos();
        void SetTileToOccupied();
        void Position(float positionX, float positionY);
        void SetGrid(GridHandlers::GridHandler& grid);
        GridHandlers::GridHandler& FetchGrid();
        void Draw(sf::RenderWindow& window);
        // Transformer koordinater, til index
        std::pair<int, int> TransformPositionToIndex(float positionX, float positionY);
        
    };
}