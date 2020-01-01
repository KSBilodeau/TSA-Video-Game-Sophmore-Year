//
//  sprite.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/30/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//
#include <SDL.h>

#include "sprite.hpp"
#include "main.hpp"

Sprite::Sprite()
{
    mTexture = nullptr;
    
    mFixed = false;
    mRectangle = {0, 0, 0, 0};
}

Sprite::~Sprite()
{
    mTexture = nullptr;
    
    mFixed = false;
    mRectangle = {0, 0, 0, 0};
}

void Sprite::free()
{
    
}

void Sprite::createSprite(int textureID, SDL_Rect &rect, bool fixed)
{
    mTexture = textureRegistry.requestAccess(textureID);
    
    mFixed = fixed;
    mRectangle = rect;
}

void Sprite::render()
{
    mTexture->render(mRectangle.x, mRectangle.y, mFixed);
}

void Sprite::update()
{
    mRectangle.x++;
}

bool Sprite::handleMouseClick(SDL_Event event)
{
    // Collision success flag
    bool success = true;
    
    return success;
}

SDL_Rect &Sprite::getRectangle()
{
    return mRectangle;
}
