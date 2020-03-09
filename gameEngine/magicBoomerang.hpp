//
//  magicBoomerang.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 2/21/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef magicBoomerang_hpp
#define magicBoomerang_hpp

#include "gameObject.hpp"
#include "textureWrapper.hpp"

#include <stdio.h>

class KBoomerang : GameObject
{
public:
    // Initialize variables
    KBoomerang();
    
    // Deallocate variable
    ~KBoomerang();
    
    // Delete boomerang
    void free() override;
    
    // Create boomerang
    void createBoomerang(SDL_Color color);
    
    void update(SDL_Event &event) override;
    
    void render() override;
    
    bool handleMouseClick(SDL_Event &event) override;
    
private:
    // Angle the projectile was sent
    double mVelAngle;
    // Angle that the sprite is rotated
    double mRotateAngle;
    
    // Color of the projectile
    SDL_Color color;
    // Collision rectangle for projectile
    SDL_Rect mRect;
};

#endif /* magicBoomerang_hpp */
