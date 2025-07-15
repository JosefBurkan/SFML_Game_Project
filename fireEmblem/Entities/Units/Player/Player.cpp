#include <iostream>
#include "../../../config.h"
#include "../Unit.cpp"
#include "../../../GridSystem/GridMovement/GridMovement.cpp"
#include <vector>
using namespace Units;
using namespace GridMovements;
using namespace GridGenerators;
using namespace Tiles;

namespace Players 
{
    class Player : public Unit 
    {

        private:
            sf::Texture texture;
            std::optional<sf::Sprite> sprite;  
            GridGenerator& gridGenerator;
            GridMovement& gridMovement;            
            int playerCurrentTileX = 0;
            int playerCurrentTileY = 0;
            int movementCooldown = 0;
            bool isSelected = false;
            bool preventSelect = false;
            sf::Vector2f realTimePos = sprite->getPosition();

        public:

            

            Player(string name, int healthPoints, string spritePath, GridGenerator& gridReference, GridMovement& gridMovement)
                : Unit(name, healthPoints, spritePath), gridGenerator(gridReference), gridMovement(gridMovement) // Fortell hvilken grid som brukes
            {
                
                if (!texture.loadFromFile(spritePath)) {
                    throw std::runtime_error("Failed to load texture!");
                }
                sprite.emplace(texture);
                sprite->setScale({3.f, 3.f});
                sprite->setPosition({5.f, 0.f});
            }

            void Draw(sf::RenderWindow& window) 
            {
                {
                    if (sprite) window.draw(*sprite);
                }
            }

        void Movement() 
        {
            std::pair<float, float> retrievedTile = gridMovement.SelectedTilePos(); // Hent hvilken grid spilleren står på
            
            float gridCurrentTileX = retrievedTile.first;
            float gridCurrentTileY = retrievedTile.second;
            movementCooldown++;

            // Logikk for å velge spilleren, og å flytte den
            if (isSelected == false && preventSelect == true)
            {
                // Flytter musen til samme rute som spilleren
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                {
                    if (playerCurrentTileX == gridCurrentTileX && playerCurrentTileY == gridCurrentTileY)
                    {
                        isSelected = true;
                        preventSelect = false;
                    }
                }
            }
            else if (isSelected == true && preventSelect == true) 
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) 
                {
                    isSelected = false;
                    preventSelect = false;
                    sprite->setPosition({gridCurrentTileX + 10, gridCurrentTileY});
                    playerCurrentTileX = gridCurrentTileX;
                    playerCurrentTileY = gridCurrentTileY;
                    gridMovement.UnSelectTile();
                }
            }

            // Gjør at man ikke kan velge, og uvelge en karakter kjempefort ved å holde 'A'
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                preventSelect = true;
            }

            if (isSelected == true)
            {
                gridMovement.SelectTile();
            }
        }

    };
}


