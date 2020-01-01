//
//  textureHandler.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/31/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#ifndef textureHandler_hpp
#define textureHandler_hpp

#include <stdio.h>
#include <map>

#include "textureWrapper.hpp"

class TextureRegister
{
public:
    // Initialize variables
    TextureRegister();
    
    // Call free all function
    ~TextureRegister();
    
    // Frees all registered textures
    void freeAll();
    
    // Frees a single texture
    void free(int textureID);
    
    // Register texture
    void registerTexture(int id, KTexture* texture);
    
    // Gives objects access to texture
    KTexture* requestAccess(int textureID);
    
private:
    // Maps all registered textures to their ids
    std::map<int, KTexture*> textures;
    
    // Maps textureIDs to the number of objects using it
    std::map<int, int> textureRegistry;
};

#endif /* textureHandler_hpp */
