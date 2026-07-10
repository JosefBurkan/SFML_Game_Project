#pragma once
#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Animations/Animation.hpp"

namespace Units
{
    class Unit;
}

namespace Sprites
{
    class Sprite
    {
        // sf::Sprite sprite;
        protected:
            Animations::Animation idle;
            Animations::Animation moving;
            Animations::Animation attacking;
            Animations::Animation dying;

            sf::Texture defaultTexture;

        public:
            Sprite();
            void play(sf::RenderWindow& window, Units::Unit* unit);
    };
}