//
//  textbox.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 2/20/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#include "textbox.hpp"
#include "main.hpp"

Textbox::Textbox()
{
    mBackgroundTexture = nullptr;
    mTextTexture = nullptr;
    
    show = true;
    
    mRectangle = {0, 0, 0, 0};
}

void Textbox::createTextbox(std::shared_ptr<KTexture> backgroundImage, std::shared_ptr<KTexture> text, int x, int y)
{
    mBackgroundTexture = std::move(backgroundImage);
    mTextTexture = std::move(text);
    
    mRectangle.x = x;
    mRectangle.y = y;
    
    mRectangle.w = mBackgroundTexture->getWidth();
    mRectangle.h = mBackgroundTexture->getHeight();
}

void Textbox::free()
{
    mBackgroundTexture = nullptr;
    mTextTexture = nullptr;
    
    show = false;
    
    mRectangle = {0, 0, 0, 0};
}

void Textbox::render()
{
    if (show)
    {
        if (mBackgroundTexture != nullptr)
            mBackgroundTexture->render(mRectangle.x, mRectangle.y, true);
        else
            printf("Textbox background texture returned null!\n");
        
        if (mTextTexture != nullptr)
            mTextTexture->render(mRectangle.x + 16, mRectangle.y + 10, true);
        else
            printf("Textbox text texture returned null!\n");
    }
}

void Textbox::update(SDL_Event &event)
{
    
}

bool Textbox::handleMouseClick(SDL_Event &event)
{
    // Click success flag
    bool success = false;
    
    int x, y;
    SDL_GetMouseState(&x, &y);
    
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(gRenderer, &mRectangle);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    if (event.type == SDL_MOUSEBUTTONDOWN && (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
    {
        if ((x < mRectangle.x + (mRectangle.w * 1.776) && x + 1 > mRectangle.x) &&
            (y < mRectangle.y + (mRectangle.h * 1.776) && y + 1 > mRectangle.y))
        {
            show = false;
            success = true;
        }
    }
    
    return success;
}

SDL_Rect &Textbox::getRectangle()
{
    return mRectangle;
}
