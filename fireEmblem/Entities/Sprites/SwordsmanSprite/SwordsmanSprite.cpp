#include "SwordsmanSprite.hpp"

namespace SwordsmanSprites
{
    SwordsmanSprite::SwordsmanSprite()
        : Sprite()
    {

        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Swordsman/Swordsman.png")) 
        {
            throw std::runtime_error("Failed to load texture!");

        }

        idle.setSpriteAndFrames(defaultTexture, 0, {0, 1, 2, 3});
        idle.setFrameSpeed(15);

        selected.setSpriteAndFrames(defaultTexture, 1, {0, 1});
        selected.setFrameSpeed(10);

        moving.setSpriteAndFrames(defaultTexture, 1, {0, 1});
        moving.setFrameSpeed(5);

        attack.setSpriteAndFrames(defaultTexture, 2, {0, 1, 2});
        attack.setFrameSpeed(25);

        attacking.setSpriteAndFrames(defaultTexture, 2, {0, 1, 2});
        attacking.setFrameSpeed(8);

        dying.setSpriteAndFrames(defaultTexture, 0, {0, 1, 2, 3});
        dying.setFrameSpeed(5);

    }
}