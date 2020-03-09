//
//  textbox.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 2/20/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef textbox_hpp
#define textbox_hpp

#include "gameObject.hpp"
#include "textureWrapper.hpp"

#include <stdio.h>

class Textbox : GameObject
{
public:
    // Initialize variables
    Textbox();
    
    void createTextbox(std::shared_ptr<KTexture> backgroundImage, std::shared_ptr<KTexture> text, int x, int y);
    
    // Free attached variables
    void free() override;
    
    // Renders GUI to screen
    void render() override;
    
    // Updates GUI
    void update(SDL_Event &event) override;
    
    // Handles input regarding the GUI
    bool handleMouseClick(SDL_Event &event) override;
    
    // Returns GUI's dimensions
    SDL_Rect &getRectangle() override;
    
private:
    // Base textures
    std::shared_ptr<KTexture> mBackgroundTexture;
    std::shared_ptr<KTexture> mTextTexture;
    
    // Show or hide bool TODO: THIS IS TEMPORARY AND WILL BE REPLACED BY TEXTBOX MANAGER
    bool show;
    
    // Coordinates
    SDL_Rect mRectangle;
};

#endif /* textbox_hpp */
