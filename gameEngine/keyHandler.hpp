//
//  eventHandler.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 2/20/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef eventHandler_hpp
#define eventHandler_hpp

#include <SDL.h>
#include <stdio.h>

class KeyHandler
{
public:
    // Initialize variables
    KeyHandler();
    
    // Deallocate variables
    ~KeyHandler();
    
    // Attaches keyboard state pointer to keyhandler
    // This is not in the constructor because SDL may not be initiated when it is called
    void startKeyHandler();
    
    // Returns a specific key's value
    bool queryKeyState(SDL_Keycode keyCode);
    
private:
    const Uint8 *keyboardStates;
};

#endif /* eventHandler_hpp */
