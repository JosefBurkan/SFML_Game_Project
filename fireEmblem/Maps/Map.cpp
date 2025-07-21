#include "../GridSystem/GridGenerator/GridGenerator.hpp"
#include "../config.h"
#include "../Entities/MapObjects/MapObject.cpp"
using namespace MapObjects;

namespace Maps 
{

    class Map 
    {
        public:
            sf::Texture texture;
            sf::RenderWindow window;

            unsigned int numberOfColumns = 15;
            unsigned int numberOfRows = 16;
            GridGenerators::GridGenerator gridGenerator;

            // For å opprette objeker, feks skog, vegger
            MapObject mapObject;
            sf::Sprite object = mapObject.GenerateSprite();

            
            void GenerateGrid() 
            {
                gridGenerator.CreateGrid(numberOfRows, numberOfColumns);
            }

            // returner gridGenerator med verdiene til den eksisterende gridden
            GridGenerators::GridGenerator& FetchGrid()
            {
                return gridGenerator;   
            }

            void LoadWindow() {
                window.create(sf::VideoMode({numberOfColumns * 50, numberOfRows * 50}), "Game Window");
            }

            sf::View LoadView()
            {
                sf::Vector2f vec1(0.f, 0.0f);
                sf::Vector2f vec2(numberOfColumns * 25, numberOfRows * 25);
                sf::View view(sf::FloatRect(vec1, vec2));
                return view;
            }

            void DrawBackground(sf::RenderWindow& window) 
            {

                texture.setSmooth(false);
                texture.loadFromFile("Grass_Background.png");
                sf:: Sprite sprite(texture);
                sprite.setScale({1.9f, 2.3f});
                window.draw(sprite);
            }

            void DrawMapObjects(sf::RenderWindow& window)
            {
                const auto& gridTiles = gridGenerator.RetrieveAllTiles();
                object.setPosition({gridTiles[10][7].RetrieveTilePos().first, gridTiles[10][7].RetrieveTilePos().second});
                window.draw(object);

            }
    };
}