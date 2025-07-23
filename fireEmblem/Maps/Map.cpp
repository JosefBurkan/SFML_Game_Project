#pragma once
#include "../GridSystem/GridGenerator/GridGenerator.hpp"
#include "../config.hpp"
#include "../Entities/MapObjects/MapObject.hpp"
#include "../Entities/MapObjects/Bat.hpp"

namespace Maps 
{

    class Map 
    {
        public:
            sf::Texture texture;
            sf::RenderWindow window;
            std::vector<MapObjects::MapObject> mapObjects;

            unsigned int numberOfColumns = 15;
            unsigned int numberOfRows = 16;
            GridGenerators::GridGenerator gridGenerator;

            // For å opprette objeker, feks skog, vegger
            MapObjects::MapObject mapObject;
            Bats::Bat mapObject2;

            sf::Sprite& object = mapObject.RetrieveSprite();
            sf::Sprite& object2 = mapObject2.RetrieveSprite();
            
            // Lag en liste med alle mapObjects her, også lag en funkjson returnerer den, slik at spiller kan iterere igjennom den
            // For å sjekke hva han står på.
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

            // Last inn kameraet
            sf::View LoadView()
            {
                sf::Vector2f vec1(0.f, 0.0f);
                sf::Vector2f vec2(numberOfColumns * 25, numberOfRows * 25);
                sf::View view(sf::FloatRect(vec1, vec2));
                return view;
            }

            // Tegn bakgrunnen
            void DrawBackground(sf::RenderWindow& window) 
            {
                texture.setSmooth(false);
                texture.loadFromFile("Grass_Background.png");
                sf:: Sprite sprite(texture);
                sprite.setScale({1.9f, 2.3f});
                window.draw(sprite);
            }

            // Sett objektet sin posisjon
            void PositionObject()
            {
                const auto& gridTiles = gridGenerator.RetrieveAllTiles();
                object.setPosition({gridTiles[10][7].RetrieveTilePos().first, gridTiles[10][7].RetrieveTilePos().second});
                object2.setPosition({gridTiles[4][4].RetrieveTilePos().first, gridTiles[4][4].RetrieveTilePos().second});

                mapObjects.push_back(mapObject);
                mapObjects.push_back(mapObject2);
            }

            // Tegn baneobjekter, feks. trær
            void DrawMapObjects(sf::RenderWindow& window)
            {
                window.draw(object);
                window.draw(object2);
            }
    };
}