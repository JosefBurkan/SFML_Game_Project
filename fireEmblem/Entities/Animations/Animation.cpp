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

        sprite.setScale({3.f, 3.f});
    }

    void Animation::setPosition(sf::Vector2f position)
    {
        sprite.setPosition(position);
    }

    sf::Vector2f Animation::getPosition()
    {
        return sprite.getPosition();
    }

    void Animation::move(sf::Vector2f direction)
    {
        sprite.move(direction);
    }

    void Animation::setSpriteAndFrames(sf::Texture& texture, int yPos, std::vector<unsigned int> rFrames)
    {
        sprite.setTexture(texture);
        line = yPos;            // + 1 slik at line ikke senre kan ganges som 0
        frames = rFrames;
    }

    void Animation::setFrameSpeed(int frameSpeed)
    {
        framesUntilDrawMax = frameSpeed;
    }

    void Animation::resetAnimation()
    {
        currentFrame = frames[0];
    }

    void Animation::animateSprite(sf::RenderWindow& window)
    {
        if (framesUntilDraw <= 0)
        {
            if (currentFrameIndex >= frames.size())
            {
                currentFrameIndex = 0;
            }

            currentFrame = frames[currentFrameIndex];

            sprite.setTextureRect(sf::IntRect({16 * currentFrame, 16 * line}, {16, 16}));

            currentFrameIndex += 1;

            framesUntilDraw = framesUntilDrawMax;
        }
        window.draw(sprite);
        framesUntilDraw--;
    }
}