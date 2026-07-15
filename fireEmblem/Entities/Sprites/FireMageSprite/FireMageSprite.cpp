#include "FireMageSprite.hpp"

namespace FireMageSprites
{
    FireMageSprite::FireMageSprite()
        : Sprite()
    {
        
        if (!defaultTexture.loadFromFile(std::string(ASSETS_DIR) + "Units/Princess/Princess.png")) 
        {
            throw std::runtime_error("Failed to load texture!");

        }

        idle.setSpriteAndFrames(defaultTexture, 0, {0, 1, 2, 3});
        idle.setFrameSpeed(10);

        selected.setSpriteAndFrames(defaultTexture, 0, {0, 3});
        selected.setFrameSpeed(5);

        moving.setSpriteAndFrames(defaultTexture, 1, {0, 1, 2, 3});
        moving.setFrameSpeed(10);

        attack.setSpriteAndFrames(defaultTexture, 3, {0, 2});
        attack.setFrameSpeed(25);

        attacking.setSpriteAndFrames(defaultTexture, 3, {0, 1, 2, 3});
        attacking.setFrameSpeed(8);

        dying.setSpriteAndFrames(defaultTexture, 2, {0, 1, 2, 3});
        dying.setFrameSpeed(5);

    }
}