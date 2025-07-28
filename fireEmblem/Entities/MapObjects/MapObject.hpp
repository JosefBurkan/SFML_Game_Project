#pragma once
#include "../../config.hpp"
#include "../../GridSystem/GridMovement/GridMovement.hpp"

namespace MapObjects
{
    class MapObject
    {
        public:
        sf::Texture texture;
        std::optional<sf::Sprite> sprite;
        std::string name = "Testobjekt ";
        GridMovements::GridMovement* gridMovement = nullptr;
        
        MapObject();
        sf::Sprite GenerateSprite();
        sf::Sprite& RetrieveSprite();
        std::pair<float, float> printPos();
        void SetTileToOccupied();
        void Position(float positionX, float positionY);
        void SetGrid(GridMovements::GridMovement& grid);
        GridMovements::GridMovement& FetchGrid();
        void Draw(sf::RenderWindow& window);
        // Transformer koordinater, til index
        std::pair<int, int> TransformPositionToIndex(float positionX, float positionY);
        
    };
}