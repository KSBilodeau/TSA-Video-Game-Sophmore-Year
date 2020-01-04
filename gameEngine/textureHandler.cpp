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
    for (std::pair<int, std::shared_ptr<KTexture>> texture : textures)
        texture.second->free();
    
    for (int i = 0; i < textures.size(); i++)
    {
        textures.erase(i);
        textureRegistry.erase(textureRegistry.begin() + i);
    }
}

void TextureRegister::free(int textureID)
{
    if (textures.at(textureID).use_count() > 1)
        printf("Texture cannot be freed: it is being used by another object!\n");
    else
    {
        textureRegistry.erase(textureRegistry.begin() + textureID);
        
        textures.at(textureID)->free();
        textures.erase(textureID);
    }
}

void TextureRegister::registerTexture(int id, KTexture baseTexture)
{
    std::shared_ptr<KTexture> texture = std::make_shared<KTexture>(baseTexture);
    
    if (!textureRegistry.empty())
    {
        textures.insert(std::make_pair(id, texture));
        textureRegistry.push_back(baseTexture);
    }
    else if (textures.count(id) == 0)
    {
        textures.insert(std::make_pair(id, texture));
        textureRegistry.push_back(baseTexture);
    }
    else
        printf("Texture has already been registered!  Request access instead.\n");
}

const std::shared_ptr<KTexture> &TextureRegister::requestAccess(int textureID)
{
    if (textures.count(textureID) == 0)
    {
        printf("Texture with id of %i has not been registered yet!\n", textureID);
        throw std::runtime_error("Access denied!\n");
    }
    else
        return textures.at(textureID);
}

void TextureRegister::renderTexture(int index)
{
    textureRegistry.at(index).render(0, 0, true);
}

KTexture TextureRegister::getTexture(int index)
{
    return textureRegistry.at(index);
}

