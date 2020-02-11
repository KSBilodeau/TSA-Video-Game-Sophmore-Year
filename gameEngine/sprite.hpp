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
#include <vector>
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
    void createSprite(int textureID, SDL_Rect &rect, bool fixed, SDL_Rect *clipRect = nullptr);
    
    // Attaches neccessary assets through passed texture
    void createSprite(std::shared_ptr<KTexture> &texture, bool fixed, SDL_Rect* clipRect = nullptr);
    
    // Free variables and textures
    void free() override;
    
    // Renders sprite to screen
    void render() override;
    
    // Updates sprite
    void update(SDL_Event &event) override;
    
    // Assign rectangle position
    void setSpritePos(int x, int y);
    
    // Handles mouse clicks on sprite
    bool handleMouseClick(SDL_Event &event) override;
    
    // Sets clipRect
    void setClipRect(SDL_Rect &rect);
    
    // Returns sprites dimensions
    SDL_Rect &getRectangle() override;
    
private:
    // Pointer to base texture
    std::shared_ptr<KTexture> mTexture;
    
    // Fixed flag
    bool mFixed;
    
    // Sprite's rectangle
    SDL_Rect mRectangle;
    
    // Texture clipRectangle
    SDL_Rect* mClipRect;
};

class AnimatedSprite : Sprite
{
public:
    // Initialize own variables
    AnimatedSprite();
    
    // Free all sprites
    void free();
    
    // Creates the animated sprite
    void createAnimatedSprite(std::shared_ptr<KTexture> &texture, int spriteSizeX, int spriteSizeY, bool fixed);
    
    // Render current sprite
    void render();
    
    // Increment current sprite
    void incrementSprite();
    
    // Decrement current sprite
    void decrementSprite();
    
    // Returns the rectangle of the current sprite
    SDL_Rect &getRectangle();
    
private:
    // Stores all sprites in the animation
    std::vector<Sprite> sprites;
    
    // Index of the sprite currently in use
    int currentSprite;
    
    // Rectangle of the current sprite
    SDL_Rect* currentRect;
};

#endif /* sprite_hpp */
