#include "Animation.hpp"

namespace Animations
{
    Animation::Animation()
        : sprite(defaultTexture)
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Pixel_Bat.png")) 
        {
            throw std::runtime_error("Failed to load texture!");

        }
    }

    void Animation::setSpriteAndFrames(sf::Texture texture, std::vector<unsigned int> rFrames)
    {
        sprite.setTexture(texture);
        frames = rFrames;
    }

    void Animation::animateSprite(sf::RenderWindow& window)
    {

        for ( int frame : frames )
        {
            sprite.setTextureRect(sf::IntRect({0, 0}, {frame * 16, frame * 16}));
            window.draw(sprite);
        }
    }
}