//
//  textureHandler.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/31/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#include "textureHandler.hpp"

TextureRegister::TextureRegister()
{
    
}

TextureRegister::~TextureRegister()
{
    freeAll();
}

void TextureRegister::freeAll()
{
    for (std::pair<int, KTexture*> texture : textures)
    {
        texture.second->free();
        
        textureRegistry.at(texture.first) = 0;
    }
    
    for (int i = 0; i < textures.size(); i++)
    {
        textures.erase(i);
        textureRegistry.erase(i);
    }
}

void TextureRegister::free(int textureID)
{
    if (textureRegistry.at(textureID) > 1)
    {
        printf("Texture cannot be freed: it is being used by another object!\n");
        textureRegistry.at(textureID)--;
    }
    else
    {
        textureRegistry.at(textureID) = 0;
        textureRegistry.erase(textureID);
        
        textures.at(textureID)->free();
        textures.erase(textureID);
    }
}

void TextureRegister::registerTexture(int id, KTexture *texture)
{
    if (textures.count(id) == 0)
    {
        textures.insert(std::make_pair(id, texture));
        textureRegistry.insert(std::make_pair(id, 1));
    }
    else
        printf("Texture has already been registered!  Request access instead.\n");
}

KTexture* TextureRegister::requestAccess(int textureID)
{
    if (textures.count(textureID) == 0)
    {
        printf("Texture with id of %i has not been registered yet!\n", textureID);
        return nullptr;
    }
    else
    {
        textureRegistry.at(textureID)++;
        return textures.at(textureID);
    }
}

