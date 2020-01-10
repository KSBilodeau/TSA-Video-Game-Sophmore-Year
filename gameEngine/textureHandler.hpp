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
#include <string>
#include <vector>

#include "textureWrapper.hpp"

class TextureAccessException : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "TextureRegistry Error: Texture retrieval access denied!\n";
    }
};

const TextureAccessException mException;

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
    void registerTexture(int id, KTexture baseTexture);
    
    // Gives objects access to texture
    const std::shared_ptr<KTexture> &requestAccess(int textureID);
    
    void renderTexture(int index);
    
    KTexture getTexture(int index);
    
private:
    KTexture texture1;
    
    // Maps all registered textures to their ids
    std::map<int, std::shared_ptr<KTexture>> textures;
    
    // Maps textureIDs to the number of objects using it
    std::vector<KTexture> textureRegistry;
};

#endif /* textureHandler_hpp */
