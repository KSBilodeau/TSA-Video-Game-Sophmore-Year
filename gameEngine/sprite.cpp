//
//  sprite.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/30/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//
#include <SDL.h>
#include <iostream>

#include "sprite.hpp"
#include "main.hpp"

Sprite::Sprite()
{
    mTexture = nullptr;
    
    mClipRect = nullptr;
    
    mFixed = false;
    mRectangle = {0, 0, 0, 0};
}

Sprite::~Sprite()
{
    mFixed = false;
    mRectangle = {0, 0, 0, 0};
}

void Sprite::free()
{
    
}

void Sprite::createSprite(int textureID, SDL_Rect &rect, bool fixed, SDL_Rect *clipRect)
{
    mTexture = nullptr;
    std::cout << (textureRegistry.requestAccess(textureID)) << " " << mTexture << "\n";
    mTexture = std::move(textureRegistry.requestAccess(textureID));
    
//    std::cout << mTexture.use_count() << " " << textureRegistry.requestAccess(textureID).use_count() << "\n";
    
    if (clipRect != nullptr)
        mClipRect = clipRect;
    
    mFixed = fixed;
    mRectangle = rect;
}

void Sprite::render()
{
    if (mClipRect != nullptr)
        mTexture->render(mRectangle.x, mRectangle.y, mFixed, mClipRect);
    else
        mTexture->render(mRectangle.x, mRectangle.y, mFixed);
}

void Sprite::update()
{
    
}

bool Sprite::handleMouseClick(SDL_Event &event)
{
    // Collision success flag
    bool success = true;
    
    return success;
}

void Sprite::setClipRect(SDL_Rect &rect)
{
    mClipRect = &rect;
}

SDL_Rect &Sprite::getRectangle()
{
    return mRectangle;
}
