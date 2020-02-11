//
//  map.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 1/12/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <fstream>
#include <cmath>

#include "map.hpp"
#include "main.hpp"

KMap::KMap()
{
    mBlockList.clear();
}

KMap::~KMap()
{
    mBlockList.clear();
}

void KMap::loadMap()
{
    for (int y = -1; y < 1; y++)
    {
        for (int x = -1; x < 1; x++)
        {
            KBlock block;
            
            block.loadDefaultTile(tiles.requestAccess(std::make_pair(0, 1)));
            block.setBlockPosition(x, y);
            mBlockList.insert(std::make_pair(std::make_pair(block.getRectangle().x, block.getRectangle().y), block));
        }
    }
    
    save();
    
    std::ifstream ifs("map.txt");
    boost::archive::text_iarchive ia(ifs);
    
    ia >> gMap;
    ifs.close();
}

void KMap::loadBlock(std::pair<int, int> coords)
{
    KBlock block;
    
    if (mBlockList.count(coords) == 0)
    {
        block.setBlockPosition(coords.first, coords.second);
        block.loadDefaultTile(tiles.requestAccess(std::make_pair(0, 1)));
        printf("Tile is being shared with %ld objects!\n", tiles.requestAccess(std::make_pair(0, 1)).use_count());
        
        std::pair<std::pair<int, int>, KBlock> blockPair = std::make_pair(coords, block);
        mBlockList.insert(blockPair);
    }
}

void KMap::eraseBlock(std::pair<int, int> coords)
{
    if (mBlockList.count(coords) != 0)
        mBlockList.erase(coords);
}

void KMap::clearMap()
{
    mBlockList.clear();
    
    for (int y = -1; y < 1; y++)
        for (int x = -1; x < 1; x++)
            loadBlock(std::make_pair(x, y));
}


void KMap::render()
{
    for (int y = gPlayer.getBlockY() - 2; y < gPlayer.getBlockY() + 2; y++)
        for (int x = gPlayer.getBlockX() - 2; x < gPlayer.getBlockX() + 2; x++)
        {
            if (mBlockList.count(std::make_pair(x, y)) != 0)
                mBlockList.at(std::make_pair(x, y)).render();
            else
            {
                loadBlock(std::make_pair(x, y));
                mBlockList.at(std::make_pair(x, y)).render();
            }
        }
}

void KMap::update(SDL_Event &event)
{
    for (int y = gPlayer.getBlockY() - 2; y < gPlayer.getBlockY() + 2; y++)
        for (int x = gPlayer.getBlockX() - 2; x < gPlayer.getBlockX() + 2; x++)
            loadBlock(std::make_pair(x, y));
    
    int x1, y1;
    SDL_GetMouseState(&x1, &y1);
    
    int x2 = std::floor(((double) x1 + camera.x) / ((double) TILE_WIDTH) / ((double) BLOCK_WIDTH));
    int y2 = std::floor(((double) y1 + camera.y) / ((double) TILE_WIDTH) / ((double) BLOCK_WIDTH));
    
    mBlockList.at(std::make_pair(x2, y2)).handleMouseClick(event);
}

void KMap::save()
{
    std::vector<std::pair<int, int>> removalArray;
    for (std::pair<std::pair<int, int>, KBlock> block : mBlockList)
        if (block.second.isEmpty())
            removalArray.push_back(block.first);
    
    for (std::pair<int, int> coord : removalArray)
        mBlockList.erase(coord);
    
    std::ofstream ofs("map.txt", std::ofstream::binary);
    boost::archive::text_oarchive oa(ofs);
    
    oa << gMap;
    ofs.close();
}

bool KMap::checkCollision(std::pair<int, int> blockCoords, SDL_Rect objectRect)
{
    // Collision flag
    bool colliding = false;
        
    for (int y = blockCoords.second - 2; y < blockCoords.second + 2; y++)
    {
        for (int x = blockCoords.first - 2; x < blockCoords.first + 2; x++)
        {
            for (std::pair<std::pair<int, int>, KTile> mappedTile : mBlockList.at(std::make_pair(x, y)).getMappedTiles())
                colliding = colliding | mappedTile.second.checkCollision(objectRect, mappedTile.second.getRectangle());
        }
    }
    
    return colliding;
}
