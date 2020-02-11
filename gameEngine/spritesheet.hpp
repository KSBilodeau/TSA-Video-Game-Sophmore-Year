//
//  spritesheet.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/30/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#ifndef spritesheet_hpp
#define spritesheet_hpp

#include <stdio.h>
#include <map>

#include "textureWrapper.hpp"
#include "sprite.hpp"

class Spritesheet
{
public:
    // Initialize variables
    Spritesheet();
    
    // Deconstructor
    ~Spritesheet();
    
    // Free variables
    void free();
    
    // Load spritesheet from image
    void loadFromFile(std::shared_ptr<KTexture> &texture, int spriteSizeX, int spriteSizeY, bool fixed);
    
    // Returns a sprite of a given id
    const std::shared_ptr<Sprite> &getSprite(int id);
    
private:
    // All loaded sprites
    std::map<int, std::shared_ptr<Sprite>> mLoadedSprites;
};

#endif /* spritesheet_hpp */
