#include "/Users/tastebutter/Desktop/mine_spill/fireEmblem/Entities/Units/Unit.hpp"
#include "Sprite.hpp"

namespace Sprites
{
    Sprite::Sprite()
    {
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Slime/Slime.png")) 
        {
            throw std::runtime_error("Failed to load texture!");

        }

        idle.setSpriteAndFrames(defaultTexture, 0, {0, 1, 2, 1});
        selected.setSpriteAndFrames(defaultTexture, 0, {0, 1, 2, 1});
        moving.setSpriteAndFrames(defaultTexture, 0, {0, 1, 2, 3});
        selected.setSpriteAndFrames(defaultTexture, 0, {0, 1, 2, 3});
        attacking.setSpriteAndFrames(defaultTexture, 0, {0, 1, 2, 3});
        dying.setSpriteAndFrames(defaultTexture, 0, {0, 1, 2, 3});
    }

    void Sprite::setPositions(sf::Vector2f position)
    {
        for (Animations::Animation* animation : animations)
        {
            animation->setPosition(position * 50.f);
        }
    }

    sf::Vector2f Sprite::getIdlePosition()
    {
        return idle.getPosition();
    }

    void Sprite::moveSprite(sf::Vector2f direction)
    {
        moving.move(direction);
    }

    void Sprite::resetAnimations()
    {
        for (Animations::Animation* animation : animations)
        {
            animation->resetAnimation();
        }
    }

    void Sprite::play(sf::RenderWindow& window, Units::Unit* unit)
    {
        using S = Units::Unit::State;

        switch(unit->state)
        {
            case S::idle:
                idle.animateSprite(window);
                break;

            case S::selected:
                selected.animateSprite(window);
                break;

            case S::moving:
                moving.animateSprite(window);
                break;

            case S::attack:
                attack.animateSprite(window);
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