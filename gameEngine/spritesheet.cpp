//
//  spritesheet.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/30/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#include "spritesheet.hpp"
#include "textureWrapper.hpp"

Spritesheet::Spritesheet()
{
    mLoadedSprites.clear();
}

void Spritesheet::free()
{
    mLoadedSprites.clear();
}

void Spritesheet::loadFromFile(std::shared_ptr<KTexture> &texture, int spriteSizeX, int spriteSizeY, bool fixed)
{
    for (int y = 0; y < texture->getHeight(); y += spriteSizeY)
    {
        for (int x = 0; x < texture->getWidth(); x += spriteSizeX)
        {
            SDL_Rect rect {x, y, spriteSizeX, spriteSizeY};
            
            std::shared_ptr<Sprite> sprite;
            sprite->createSprite(texture, fixed, &rect);
            
            mLoadedSprites.insert(std::make_pair(x + (y * texture->getWidth()), sprite));
        }
    }
}

const std::shared_ptr<Sprite> &Spritesheet::getSprite(int id)
{
    return mLoadedSprites.at(id);
}
