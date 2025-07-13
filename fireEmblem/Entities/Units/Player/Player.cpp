#include <iostream>
#include "../Unit.cpp"
#include "../../../GridSystem/GridGenerator.cpp"
#include "../../../GridSystem/Tile.cpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace Units;
using namespace GridGenerators;
using namespace Tiles;

namespace Players 
{
    class Player : public Unit 
    {

        private:
            sf::Texture texture;
            std::optional<sf::Sprite> sprite;  
            GridGenerator& gridGenerator;       // Hent eksisterende grid
            int playerCurrentTileX = 0;
            int playerCurrentTileY = 0;
            bool isSelected = false;
            sf::Vector2f realTimePos = sprite->getPosition();

        public:
            Player(string name, int healthPoints, string spritePath, GridGenerator& gridReference)
                : Unit(name, healthPoints, spritePath), gridGenerator(gridReference) // Fortell hvilken grid som brukes
            {
                if (!texture.loadFromFile(spritePath)) {
                    throw std::runtime_error("Failed to load texture!");
                }
                sprite.emplace(texture);
                sprite->setScale({3.f, 3.f});
                sprite->setPosition({25.f, 25.f});
            }

            void Draw(sf::RenderWindow& window) 
            {
                {
                    if (sprite) window.draw(*sprite);
                }
            }

        void Movement() 
        {
            std::pair<float, float> retrievedTile = gridGenerator.SelectedTilePos(); // Hent hvilken grid spilleren står på
            
            float gridCurrentTileX = retrievedTile.first;
            float gridCurrentTileY = retrievedTile.second;

            // Flytter spilleren til den ruten man trykker 'A' på
            if (isSelected == true) 
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) 
                {
                    isSelected = false;
                    sprite->setPosition({gridCurrentTileX + 10, gridCurrentTileY});
                    playerCurrentTileX = gridCurrentTileX;
                    playerCurrentTileY = gridCurrentTileY;
                }
            }


            // Flytter musen til samme rute som spilleren
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                if (playerCurrentTileX == gridCurrentTileX && playerCurrentTileY == gridCurrentTileY)
                {
                    isSelected = true;
                }
            }

            if (isSelected == true)
            {
                gridGenerator.SelectTile();
            }


        }

    };
}


