//
//  textureWrapper.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/30/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//
#include "textureWrapper.hpp"
#include "main.hpp"

#include <type_traits>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cmath>

KTexture::KTexture()
{
    mTexture = nullptr;
    
    mWidth = 0;
    mHeight = 0;
    
    mXScale = 0;
    mYScale = 0;
}

void KTexture::free()
{
    mWidth = 0;
    mHeight = 0;
    
    mXScale = 0;
    mYScale = 0;
}

bool KTexture::loadFromFile(std::string path, double scale)
{
    // Loading success flag
    bool success = true;
    
    // Free any previous textures
    free();
    
    // Load image from path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        printf("Unable to load image at %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        success = false;
    }
    // If image was loaded and applied to surface
    else
    {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0, 0xDC));
        
        // Create texture from surface
        mTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(gRenderer, loadedSurface), [](SDL_Texture* texture) {SDL_DestroyTexture(texture);});
        if (mTexture == nullptr)
        {
            printf("Unable to create texture from image at %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
            success = false;
        }
        // If a texture was successfully created from surface
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
    }
    
    // Set scale
    mXScale = scale;
    mYScale = scale;
    
    // Get rid of the old surface
    SDL_FreeSurface(loadedSurface);
    
    return success;
}

bool KTexture::loadFromString(std::string text, SDL_Color textColor)
{
    // Loading success flag
    bool success = true;
    
    // Get rid of preexisting texture
    free();
    
    // Render text to surface
    printf("%s", text.c_str());
    SDL_Surface* loadedSurface = TTF_RenderText_Blended_Wrapped(gFont, text.c_str(), textColor, 300 * 1.776);
    if (loadedSurface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    // If image was loaded and applied to surface
    else
    {
        // Create texture from surface
        mTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(gRenderer, loadedSurface), [](SDL_Texture* texture) {SDL_DestroyTexture(texture);});
        if (mTexture == nullptr)
        {
            printf("Unable to create texture from rendered text! SDL_image Error: %s\n", IMG_GetError());
            success = false;
        }
        // If a texture was successfully created from surface
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
    }
    
    // Sets scale
    mXScale = 1;
    mYScale = 1;
    
    // Get rid of the old surface
    SDL_FreeSurface(loadedSurface);
    
    return success;
}

void KTexture::render(int x, int y, bool fixed, SDL_Rect* clipRect)
{
    SDL_Rect renderQuad;
    
    // The rectangle the image will be rendered to
    if (fixed)
        renderQuad = {x, y, mWidth, mHeight};
    else
        renderQuad = {x - camera.x, y - camera.y, mWidth, mHeight};
    
    // Applies clip dimensions to rendering quad
    if (clipRect != nullptr)
    {
        renderQuad.w = clipRect->w;
        renderQuad.h = clipRect->h;
    }
    
    renderQuad.w *= mXScale;
    renderQuad.h *= mYScale;
    
    SDL_RenderCopy(gRenderer, mTexture.get(), clipRect, &renderQuad);
}

void KTexture::setBlendMode(SDL_BlendMode blendMode)
{
    SDL_SetTextureBlendMode(mTexture.get(), blendMode);
}

void KTexture::modifyTextureColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture.get(), red, green, blue);
}

void KTexture::modifyAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture.get(), alpha);
}

void KTexture::modifyTextureScale(double xScale, double yScale)
{
    mXScale = xScale;
    mYScale = yScale;
}

int KTexture::getWidth()
{
    return mWidth;
}

int KTexture::getHeight()
{
    return mHeight;
}
