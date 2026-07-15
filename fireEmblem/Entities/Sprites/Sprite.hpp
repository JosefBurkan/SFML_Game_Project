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
            Animations::Animation selected;
            Animations::Animation moving;
            Animations::Animation attack;
            Animations::Animation attacking;
            Animations::Animation dying;

            std::array<Animations::Animation*, 6> animations = {&idle, &selected, &moving, &attack, &attacking, &dying};

            sf::Texture defaultTexture;

        public:
            Sprite();
            sf::Vector2f getIdlePosition();
            void resetAnimations();                                     // Sett sprite indes tilbake til 0
            void setPositions(sf::Vector2f position);                   // Flytt alle sprites
            void moveSprite(sf::Vector2f direction);                    // Flytt kun movingsprite
            void play(sf::RenderWindow& window, Units::Unit* unit);
    };
}