//
//  tile.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 1/12/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#include "tile.hpp"
#include "main.hpp"

#include <iostream>

// THIS IS THE START OF THE TILESHEET METHOD DECLARATION AREA

KTilesheet::KTilesheet()
{
    
}

void KTilesheet::free()
{
    
}

void KTilesheet::loadFromTexture(int textureID, int tileSizeX, int tileSizeY)
{
    std::shared_ptr<KTexture> texture = textureRegistry.requestAccess(textureID);
    
    for (int y = 0; y < texture->getHeight(); y += tileSizeX)
    {
        for (int x = 0; x < texture->getWidth(); x += tileSizeY)
        {
            KTile tile;
            SDL_Rect rect {x, y, tileSizeX, tileSizeY};
            tile.loadFromTexture(textureID, rect, &rect);
            
            if (tileRegistry.empty())
            {
                tiles.insert(std::make_pair(std::make_pair(x / tileSizeX, y / tileSizeY), std::make_shared<KTile>(tile)));
                tileRegistry.push_back(std::make_shared<KTile>(tile));
            }
            else if (tiles.count(std::make_pair(x, y)) == 0)
            {
                tiles.insert(std::make_pair(std::make_pair(x / tileSizeX, y / tileSizeY), std::make_shared<KTile>(tile)));
                tileRegistry.push_back(std::make_shared<KTile>(tile));
            }
            else
                printf("This tile with an id of %i is already registered!", textureID);
        }
    }
}

std::shared_ptr<KTile> &KTilesheet::requestAccess(std::pair<int, int> tileID)
{
    if (tiles.count(tileID) == 0)
    {
        printf("Texture with id of (%i, %i) has not been registered yet!\n", tileID.first, tileID.second);
        throw mException;
    }
    else
        return tiles.at(tileID);
}

// THIS IS THE END OF THE TILESHEET METHOD DECLARATION  AREA

// THIS IS THE START OF THE TILE METHOD DECLARATION AREA

KTile::KTile()
{
    collidable = false;
    textureID = 0;
    
    mRect = {0, 0, 0, 0};
    mClipRect = {0, 0, 0, 0};
}

void KTile::free()
{
    collidable = false;
    textureID = 0;
    
    mRect = {0, 0, 0, 0};
    mClipRect = {0, 0, 0, 0};
}

void KTile::loadFromTexture(int textureID, SDL_Rect &rectangle, SDL_Rect* clipRect)
{
    mRect = rectangle;
    
    if (clipRect != nullptr)
        mClipRect = *clipRect;
    else
        mClipRect.x = -1;
    
    mTexture = textureRegistry.requestAccess(textureID);
}

void KTile::moveTo(int x, int y)
{
    mRect.x = x;
    mRect.y = y;
}

void KTile::render(int blockX, int blockY)
{
    if (mClipRect.x != -1)
        mTexture->render(blockX, blockY, false, &mClipRect);
    else
        mTexture->render(blockX, blockY, false);
    
    SDL_Rect rect {(mRect.x * (16 * SCALE_FACTOR)) - camera.x, (mRect.y * (16 * SCALE_FACTOR)) - camera.y, (16 * SCALE_FACTOR), (16 * SCALE_FACTOR)};
    SDL_RenderDrawRect(gRenderer, &rect);
}

bool KTile::checkCollision(SDL_Rect &rect1, SDL_Rect &rect2)
{
    // Collision flag
    bool colliding = false;

    SDL_Rect tileRect {(rect2.x) - camera.x, (rect2.y) - camera.y, rect2.w, rect2.h};
    SDL_Rect player {(rect1.x) - camera.x, (rect1.y) - camera.y, rect1.w, rect1.h + 2};
    
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(gRenderer, &tileRect);
    SDL_RenderDrawRect(gRenderer, &player);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    if ((player.x < tileRect.x + tileRect.w && player.x + player.w > tileRect.x) &&
        (player.y < tileRect.y + tileRect.h && player.y + player.h > tileRect.y))
    {
        colliding = true;
    }

    return colliding;
}

SDL_Rect &KTile::getRectangle()
{
    return mRect;
}

// THIS IS THE END OF THE TILE METHOD DECLARATION AREA
