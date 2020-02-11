//
//  gameObject.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/31/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#ifndef gameObject_hpp
#define gameObject_hpp

#include <stdio.h>
#include <SDL.h>

class GameObject
{
public:
    // Virtual deconstructor
    virtual ~GameObject() = 0;
    
    // Frees variables
    virtual void free() = 0;
    
    // Renders game object to screen
    virtual void render() = 0;
    
    // Updates game object
    virtual void update(SDL_Event &event) = 0;
    
    // Handle mouse clicks in relation to game object
    virtual bool handleMouseClick(SDL_Event &event) = 0;
    
    // Returns game object's dimensions
    virtual SDL_Rect &getRectangle() = 0;
};

#endif /* gameObject_hpp */
