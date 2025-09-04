#include "Slime.hpp"

namespace Slimes
{
    Slime::Slime(GridGenerators::GridGenerator& gridReference, Maps::Map& map, AttackManagers::AttackManager& attacks)
        : Unit(gridReference, map, attacks)
    {
        if (!texture.loadFromFile(std::string(ASSETS_DIR) + "Slime-2.png")) 
        {
            throw std::runtime_error("Failed to load texture!");

        }

        name = "Slime";

        sprite.emplace(texture);
        sprite->setTextureRect(sf::IntRect({0, 0}, {16, 16}));
        sprite->setScale({3.f, 3.f});
        sprite->setPosition({350.f, 150.f});
    }

    void Slime::Draw(sf::RenderWindow& window)
    {
        framesUntilDraw++;

        if (framesUntilDraw >= 8)
        {
            while (textureLocationX >= 48)
            {
                textureLocationY += 16;
                textureLocationX = 0;

                if (textureLocationY >= 48)
                {
                    textureLocationY = 0;
                }
            }
            sprite->setTextureRect(sf::IntRect({textureLocationX, textureLocationY}, {16, 16}));

            textureLocationX += 16;

            framesUntilDraw = 0;
        }

        window.draw(*sprite);

    }



}