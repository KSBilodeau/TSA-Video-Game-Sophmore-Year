//
//  sprite.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/30/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#ifndef sprite_hpp
#define sprite_hpp

#include <stdio.h>
#include <SDL.h>

#include "gameObject.hpp"
#include "textureWrapper.hpp"

class Sprite : public GameObject
{
public:
    // Initialize sprite variables
    Sprite();
    
    // Call free function
    ~Sprite();
    
    // Attaches neccessary assets
    void createSprite(int textureID, SDL_Rect &rect, bool fixed);
    
    // Free variables and textures
    void free() override;
    
    // Renders sprite to screen
    void render() override;
    
    // Updates sprite
    void update() override;
    
    // Handles mouse clicks on sprite
    bool handleMouseClick(SDL_Event &event) override;
    
    // Returns sprites dimensions
    SDL_Rect &getRectangle() override;
    
private:
    // Pointer to base texture
    std::shared_ptr<KTexture> mTexture;
    
    // Fixed flag
    bool mFixed;
    
    // Sprite's rectangle
    SDL_Rect mRectangle;
};

class AnimatedSprite : Sprite
{
    
};

#endif /* sprite_hpp */
