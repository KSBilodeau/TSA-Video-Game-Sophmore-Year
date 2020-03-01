//
//  block.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 1/12/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#include "block.hpp"
#include "main.hpp"

#include <cmath>

KBlock::KBlock()
{
    mRectangle = {0, 0, 0, 0};
    
    mMappedTiles.empty();
}

void KBlock::free()
{
    mRectangle = {0, 0, 0, 0};
    
    mMappedTiles.empty();
}

void KBlock::loadDefaultTile(std::shared_ptr<KTile> defaultTile)
{
    mDefaultTile = std::move(defaultTile);
}

void KBlock::render()
{
    for (int y = 0; y < BLOCK_HEIGHT; y++)
    {
        for (int x = 0; x < BLOCK_WIDTH; x++)
        {
            mDefaultTile->moveTo(x + (mRectangle.x * BLOCK_WIDTH), y + (mRectangle.y * BLOCK_HEIGHT));
            mDefaultTile->render(mDefaultTile->getRectangle().x * 48, mDefaultTile->getRectangle().y * 48);
        }
    }
    
    for (auto &tileArray : mMappedTiles)
        tileArray.second.render(tileArray.second.getRectangle().x, tileArray.second.getRectangle().y);
}

void KBlock::setBlockPosition(int x, int y)
{
    mRectangle.x = x;
    mRectangle.y = y;
    
    mRectangle.w = BLOCK_WIDTH;
    mRectangle.h = BLOCK_HEIGHT;
}

void KBlock::handleMouseClick(SDL_Event &event)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    
    double x1, y1;
    x1 = ((double) (x + (camera.x)) / (TILE_WIDTH));
    y1 = ((double) (y + (camera.y)) / (TILE_HEIGHT));
    
    x1 = std::floor(x1);
    y1 = std::floor(y1);
    
    if (mMappedTiles.count(std::make_pair(x1, y1)) != 0 && (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)))
        mMappedTiles.erase(std::make_pair(x1, y1));
    else if (mMappedTiles.count(std::make_pair(x1, y1)) == 0 && (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
    {
        tiles.requestAccess(selectedTileID)->moveTo(x1 * TILE_WIDTH, y1 * TILE_HEIGHT);
        mMappedTiles.insert(std::make_pair(std::make_pair(x1, y1), *tiles.requestAccess(selectedTileID).get()));
    }
}

bool KBlock::isEmpty()
{
    return mMappedTiles.empty();
}

std::map<std::pair<int, int>, KTile> &KBlock::getMappedTiles()
{
    return mMappedTiles;
}

SDL_Rect &KBlock::getRectangle()
{
    return mRectangle;
}
