//
//  gui.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/30/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#ifndef gui_hpp
#define gui_hpp

#include <stdio.h>
#include <SDL.h>

#include "gameObject.hpp"
#include "textureWrapper.hpp"

class MainMenu : GameObject
{
public:
    // Initialize variables
    MainMenu();
    
    void createMainMenu(int textureID, int x, int y);
    
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
    // Base texture
    KTexture* mTexture;
    
    // Coordinates
    SDL_Rect mRectangle;
};

#endif /* gui_hpp */
