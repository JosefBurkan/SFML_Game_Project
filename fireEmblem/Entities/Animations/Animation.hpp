#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/config.hpp"

// Skal brukes av Sprites. 

namespace Animations
{
    class Animation
    {
        private:
            std::vector<unsigned int> frames;
            int line = 0;                       // linjen i spritesheeten som spriten skal lese fra
            int framesUntilDraw = 0;
            int framesUntilDrawMax = 10;
            int currentFrameIndex = 0;
            int currentFrame = 0;
            int frameSpeed = 0;

            sf::Texture defaultTexture;
            sf::Sprite sprite;

            

        public:
            Animation();
            sf::Vector2f getPosition();
            void setPosition(sf::Vector2f position);
            void move(sf::Vector2f direction);

            void setSpriteAndFrames(sf::Texture& texture, int yPos,  std::vector<unsigned int> rFrames);
            void setFrameSpeed(int frameSpeed);
            void resetAnimation();

            void animateSprite(sf::RenderWindow& window);
    };
}