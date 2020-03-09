//
//  player.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 1/13/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//
#include <cmath>
#include <iostream>

#include "player.hpp"
#include "main.hpp"

Player::Player()
{
    mTexture = nullptr;
    
    mRect = {0, 0, 0, 0};
    
    for (int y = 0; y < (sizeof(mClipRects) / sizeof(*mClipRects)); y++)
        for (int x = 0; x < (sizeof(mClipRects[y]) / sizeof(*mClipRects[y])); x++)
            mClipRects[y][x] = {0, 0, 0, 0};
    
    xVelocityDirection = false;
    yVelocityDirection = false;
    
    mBlockX = 0;
    mBlockY = 0;
    
    speed = 4;
    
    xVelocity = 0;
    yVelocity = 0;
    
    ticks = 0;
}

Player::~Player()
{
    mTexture = nullptr;
    
    mRect = {0, 0, 0, 0};
    
    for (int y = 0; y < (sizeof(mClipRects) / sizeof(*mClipRects)); y++)
        for (int x = 0; x < (sizeof(mClipRects[y]) / sizeof(*mClipRects[y])); x++)
            mClipRects[y][x] = {0, 0, 0, 0};
    
    mBlockX = 0;
    mBlockY = 0;
    
    speed = 0;
    
    xVelocity = 0;
    yVelocity = 0;
    
    ticks = 0;
}

void Player::createPlayer(std::shared_ptr<KTexture> texture, int spriteSizeX, int spriteSizeY, SDL_Rect &startingRect)
{
    mTexture = std::move(texture);
    
    for (int y = 0; y < (sizeof(mClipRects) / sizeof(*mClipRects) * spriteSizeY); y += spriteSizeY)
        for (int x = 0; x < (sizeof(mClipRects[y]) / sizeof(*mClipRects[y]) * spriteSizeX); x += spriteSizeX)
            mClipRects[y / spriteSizeY][x / spriteSizeX] = {x, y, spriteSizeX, spriteSizeY};
    
    mRect.x = startingRect.x;
    mRect.y = startingRect.y;
    
    mRect.w = startingRect.w;
    mRect.h = startingRect.h;
}

void Player::update(SDL_Event &event)
{
    // Checks if key is pressed
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        // Forwards keys are W and UP ARROW
        if (event.key.keysym.sym == SDLK_w)
        {
            yVelocity -= 1.0;
            mDirection = 2;
        }
        // Down keys are S and DOWN ARROW
        else if (event.key.keysym.sym == SDLK_s)
        {
            yVelocity += 1.0;
            mDirection = 3;
        }
        // Left keys are A and LEFT ARROW
        else if (event.key.keysym.sym == SDLK_a)
        {
            xVelocity -= 1.0;
            mDirection = 1;
        }
        // Right keys are D and RIGHT ARROW
        else if (event.key.keysym.sym == SDLK_d)
        {
            xVelocity += 1.0;
            mDirection = 0;
        }
    }
    
    // Checks if key has been released
    if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        // Forwards keys are W and UP ARROW
        if (event.key.keysym.sym == SDLK_w)
            yVelocity += 1.0;
        // Down keys are S and DOWN ARROW
        else if (event.key.keysym.sym == SDLK_s)
            yVelocity -= 1.0;
        // Left keys are A and LEFT ARROW
        else if (event.key.keysym.sym == SDLK_a)
            xVelocity += 1.0;
        // Right keys are D and RIGHT ARROW
        else if (event.key.keysym.sym == SDLK_d)
            xVelocity -= 1.0;
    }
}

void Player::render()
{
    // Renders player texture at its location
    mTexture->render(mRect.x, mRect.y, false, &mClipRects[mDirection][mCurrentSprite]);
    
    // Draws players noncollision rectangle
//    SDL_Rect noncollisionRect {mRect.x - camera.x, mRect.y - camera.y, mRect.w, mRect.h};
//    SDL_RenderDrawRect(gRenderer, &noncollisionRect);
}

void Player::move()
{
    // Used in cases where player is moving diagonally
//    float normalizeX = 0, normalizeY = 0;
//    double len = 0;
    
    if (xVelocity != 0 || yVelocity != 0)
        isMoving = true;
    else
        isMoving = false;
    
//    if (xVelocity != 0)
//        movingX = true;
//    else
//        movingX = false;
//
//    if (yVelocity != 0)
//        movingY = true;
//    else
//        movingY = false;
    
    if (isMoving)
    {
//        if (movingX)
//        {
//            if (xVelocity < 0 && mDirection != 1)
//                mDirection = 1;
//            else if (xVelocity > 0 && mDirection != 0)
//                mDirection = 0;
//        }
//        else if (movingY)
//        {
//            if (yVelocity < 0 && mDirection != 2)
//                mDirection = 2;
//            else if (yVelocity > 0 && mDirection != 3)
//                mDirection = 3;
//        }
//
//        if (movingX && movingY)
//        {
//            len = std::sqrt((std::pow(xVelocity, 2) + std::pow(yVelocity, 2)));
//
//            normalizeX = xVelocity / len * speed;
//            normalizeY = yVelocity / len * speed;
//        }
        
        // Move player along the x-axis
        mRect.x += xVelocity * speed;
            
        if (gMap.checkCollision(std::make_pair(mBlockX, mBlockY), mRect))
            mRect.x -= xVelocity * speed;
        
        // Move player along the y-axis
        mRect.y += yVelocity * speed;
        
        if (gMap.checkCollision(std::make_pair(mBlockX, mBlockY), mRect))
            mRect.y -= yVelocity * speed;
        
        if (!(mCurrentSprite < 7))
            mCurrentSprite = 0;
        else if (ticks % 5 == 0)
            mCurrentSprite++;
    }
    else
        mCurrentSprite = 0;
    
    mBlockX = std::floor(((double) mRect.x) / ((double) TILE_WIDTH) / ((double) BLOCK_WIDTH));
    mBlockY = std::floor(((double) mRect.y) / ((double) TILE_HEIGHT) / ((double) BLOCK_HEIGHT));
    
    for (int y = mBlockY - 2; y < mBlockY + 2; y++)
    {
        for (int x = mBlockX - 2; x < mBlockX + 2; x++)
        {
            gMap.loadBlock(std::make_pair(x, y));
        }
    }
        
    updateCamera();
    ticks++;
}

void Player::updateCamera()
{
    camera.x = mRect.x - (camera.w / 2);
    camera.y = mRect.y - (camera.h / 2);
}

int &Player::getXPos()
{
    return mRect.x;
}

int &Player::getYPos()
{
    return mRect.y;
}

int &Player::getBlockX()
{
    return mBlockX;
}

int &Player::getBlockY()
{
    return mBlockY;
}

int &Player::getWidth()
{
    return mRect.w;
}

int &Player::getHeight()
{
    return mRect.h;
}

SDL_Rect &Player::getRectangle()
{
    return mRect;
}


