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

class MainMenuButton : GameObject
{
public:
    // Initialize variable
    MainMenuButton();
    
    // Renders button to screen
    void render() override;
    
    // Updates button?
    void update() override;
    
    // Handles mouse clicks on button
    bool handleMouseClick(SDL_Event event) override;
    
    // Returns button's dimensions
    SDL_Rect& getRectangle() override;
    
private:
    // Base texture
    KTexture* mBackgroundTexture;
    
    // Icon texture
    KTexture* mIcon;
    
    // Buttons location
    int x, y;
};

#endif /* guiButtons_hpp */
