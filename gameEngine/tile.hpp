//
//  tile.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 1/12/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef tile_hpp
#define tile_hpp

#include <stdio.h>
#include <map>
#include <vector>

#include "textureWrapper.hpp"

#include <boost/serialization/serialization.hpp>
#include <SDL.h>

class KTile
{
public:
    // Initialize variables
    KTile();
    
    // Free variables
    void free();
    
    // Apply texture
    void loadFromTexture(int textureID, SDL_Rect &rectangle, SDL_Rect* clipRect = nullptr);
    
    // Serialize tile
    template<class Archive>
    void serialize(Archive &ar, unsigned int version)
    {
        ar & mRect.x;
        ar & mRect.y;
        ar & mRect.w;
        ar & mRect.h;
        
        ar & mClipRect.x;
        ar & mClipRect.y;
        ar & mClipRect.w;
        ar & mClipRect.h;
        
        ar & textureID;
        ar & collidable;
    }
    
    // Sets tile to new texture
    void setTileTexture(std::shared_ptr<KTexture> &texture);
    
    // Set rectangle location
    void moveTo(int x, int y);
    
    // Renders tile
    void render(int blockX, int blockY);
    
    // Checks if tile is colliding with another rectangle
    bool checkCollision(SDL_Rect &rect1, SDL_Rect &rect2);
    
    // Return tile dimensions
    SDL_Rect &getRectangle();
    
private:
    // Base texture for tile
    std::shared_ptr<KTexture> mTexture;
    
    // Tiles rectangle
    SDL_Rect mRect;
    
    // Tile's clipRectangle for base texture
    SDL_Rect mClipRect;
    
    // ID of the texture that is going to be used
    int textureID;
    
    // Stores if the tile is collidable
    bool collidable;
};

class KTilesheet
{
public:
    // Initialize variables
    KTilesheet();
    
    // Deallocate variables
    void free();
    
    // Load tile set from texture
    void loadFromTexture(int textureID, int tileSizeX, int tileSizeY);
    
    // Get tile pointer
    std::shared_ptr<KTile> &requestAccess(std::pair<int, int> tileID);
    
private:
    // Maps all registered tiles to their ids
    std::map<std::pair<int, int>, std::shared_ptr<KTile>> tiles;
    
    // Maps textureIDs to the number of objects using it
    std::vector<std::shared_ptr<KTile>> tileRegistry;
};

#endif /* tile_hpp */
