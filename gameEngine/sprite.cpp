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

// THIS IS THE START OF THE SPRITE METHOD DECLARATION AREA

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
    mTexture = std::move(textureRegistry.requestAccess(textureID));
    
    if (clipRect != nullptr)
        mClipRect = clipRect;
    
    mFixed = fixed;
    mRectangle = rect;
}

void Sprite::createSprite(std::shared_ptr<KTexture> &texture, bool fixed, SDL_Rect* clipRect)
{
    mTexture->free();
    mTexture = std::move(texture);
    
    mFixed = fixed;
    
    if (clipRect != nullptr)
        mClipRect = clipRect;
}

void Sprite::render()
{
    if (mClipRect != nullptr)
        mTexture->render(mRectangle.x, mRectangle.y, mFixed, mClipRect);
    else
        mTexture->render(mRectangle.x, mRectangle.y, mFixed);
}

void Sprite::update(SDL_Event &event)
{
    
}

void Sprite::setSpritePos(int x, int y)
{
    mRectangle.x = x;
    mRectangle.y = y;
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

// THIS IS THE END OF THE SPRITE METHOD DECLARTION AREA
