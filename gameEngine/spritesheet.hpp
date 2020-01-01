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

#include "textureWrapper.hpp"

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
    void loadFromFile(KTexture texture, SDL_Rect rect);
};

#endif /* spritesheet_hpp */
