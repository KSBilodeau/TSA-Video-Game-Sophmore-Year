//
//  player.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 1/13/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <SDL.h>

#include "sprite.hpp"
#include "spritesheet.hpp"

class Player : GameObject
{
public:
    // Initialize variables
    Player();
    
    // Deallocate variables
    ~Player();
    
    // Deconstructor works just fine
    void free() override {};
    
    // Add actual values to the variables
    void createPlayer(std::shared_ptr<KTexture> texture, int spriteSizeX, int spriteSizeY, SDL_Rect &startingRect);
    
    // Handles key presses related to player movement
    void update(SDL_Event &event) override;
    
    // Renders the player to screen
    void render() override;
    
    // Moves player based off directional data handled by update
    void move();
    
    // Update camera's position based off player's position
    void updateCamera();
    
    // Function is not used by player game object
    bool handleMouseClick(SDL_Event &event) override { return false; };
    
    // Returns players x and y positions as references
    int &getXPos();
    int &getYPos();
    
    // Returns the x and y position of the block the player is in
    int &getBlockX();
    int &getBlockY();
    
    // Returns players width and height
    int &getWidth();
    int &getHeight();
    
    // Returns player's whole rectangle
    SDL_Rect &getRectangle() override;
    
private:
    // Player's base texure
    std::shared_ptr<KTexture> mTexture;
    
    // Player's main rectangle
    SDL_Rect mRect;
    
    // Player's animation clip rectangles
    SDL_Rect mClipRects[4][8];
    
    // Player's block coordinates
    int mBlockX;
    int mBlockY;
    
    // Players movement in pixels per tick
    int speed;
    
    // Player's movement position
    double xVelocity;
    double yVelocity;
    
    // Bools for which axis the player is moving on
    bool movingX, movingY;
    
    // False for left, true for right
    bool xVelocityDirection;
    // False for up, true for down
    bool yVelocityDirection;
    
    // TODO: Remember what this variable does exactly
    // I think this variable is used for movement normalization, but not completely sure
    int ticks;
    
    // Player's movement flag
    bool isMoving;
    
    // Player's current direction
    int mDirection;
    
    // Player's current sprite (index of its clip rectangle)
    int mCurrentSprite;
};

#endif /* player_hpp */
