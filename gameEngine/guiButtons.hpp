//
//  guiButtons.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/31/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#ifndef guiButtons_hpp
#define guiButtons_hpp

#include <stdio.h>

#include "gameObject.hpp"
#include "textureWrapper.hpp"

class GUIButton : GameObject
{
public:
    // Pure virtual deconstructor
    virtual ~GUIButton() = 0;
    
    // Called by handle mouse click
    virtual void activate() = 0;
};

class MainMenuButton : GUIButton
{
public:
    // Initialize variable
    MainMenuButton();
    
    // Creates a gui button
    void createMainMenuButton(std::shared_ptr<KTexture> backgroundTexture, std::shared_ptr<KTexture> icon, int x, int y, SDL_Rect rects[2]);
    
    // Renders button to screen
    void render() override;
    
    // Updates button?
    void update() override;
    
    // Frees everything maybe?
    void free() override;
    
    // Handles mouse clicks on button
    bool handleMouseClick(SDL_Event &event) override;
    
    // Does whatever this button is supposed to do
    void activate() override;
    
    // Returns button's dimensions
    SDL_Rect& getRectangle() override;
    
private:
    // Base texture
    std::shared_ptr<KTexture> mBackgroundTexture;
    
    // Icon texture
    std::shared_ptr<KTexture> mIcon;
    
    // Selection flag
    bool isSelected;
    
    // Buttons dimensions
    SDL_Rect mRectangle;
    
    // Texture clip rectangles
    SDL_Rect mClipRects[2];
};

#endif /* guiButtons_hpp */
