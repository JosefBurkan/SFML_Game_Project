#include "SlimeSprite.hpp"

namespace SlimeSprites
{
    SlimeSprite::SlimeSprite()
        : Sprite()
    {

        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Slime/Slime.png")) 
        {
            throw std::runtime_error("Failed to load texture!");

        }

        idle.setSpriteAndFrames(defaultTexture, 0, {0, 1, 2, 3, 4, 3, 2});
        idle.setFrameSpeed(9);

        selected.setSpriteAndFrames(defaultTexture, 0, {0, 1});
        selected.setFrameSpeed(10);

        moving.setSpriteAndFrames(defaultTexture, 0, {0, 1});
        moving.setFrameSpeed(5);

        attack.setSpriteAndFrames(defaultTexture, 0, {0, 1, 2});
        attack.setFrameSpeed(25);

        attacking.setSpriteAndFrames(defaultTexture, 0, {0, 1, 2});
        attacking.setFrameSpeed(8);

        dying.setSpriteAndFrames(defaultTexture, 1, {0, 1, 2, 3, 4, 5});
        dying.setFrameSpeed(9);

    }
}