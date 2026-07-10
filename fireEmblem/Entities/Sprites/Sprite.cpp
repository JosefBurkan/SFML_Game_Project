#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Unit.hpp"
#include "Sprite.hpp"

namespace Sprites
{
    Sprite::Sprite()
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Pixel_Bat.png")) 
        {
            throw std::runtime_error("Failed to load texture!");

        }

        idle.setSpriteAndFrames(defaultTexture, {0, 1, 2, 3});
        moving.setSpriteAndFrames(defaultTexture, {0, 1, 2, 3});
        attacking.setSpriteAndFrames(defaultTexture, {0, 1, 2, 3});
        dying.setSpriteAndFrames(defaultTexture, {0, 1, 2, 3});

    }

    void Sprite::play(sf::RenderWindow& window, Units::Unit* unit)
    {
        using S = Units::Unit::State;

        switch(unit->state)
        {
            case S::idle:
                idle.animateSprite(window);
                break;

            case S::moving:
                moving.animateSprite(window);
                break;
            
            case S::attacking:
                attacking.animateSprite(window);
                break;

            case S::dying:
                dying.animateSprite(window);
                break;
        }
    }
}