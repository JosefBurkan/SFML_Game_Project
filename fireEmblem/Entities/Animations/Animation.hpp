#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/config.hpp"

// Skal brukes av Sprites. 

namespace Animations
{
    class Animation
    {
        private:
            std::vector<unsigned int> frames;
            sf::Texture defaultTexture;
            sf::Sprite sprite;
            

        public:
            Animation();
            void setSpriteAndFrames(sf::Texture texture, std::vector<unsigned int> rFrames);
            void animateSprite(sf::RenderWindow& window);
    };
}