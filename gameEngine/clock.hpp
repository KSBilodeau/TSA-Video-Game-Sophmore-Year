//
//  clock.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/31/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#ifndef clock_hpp
#define clock_hpp

#include <stdio.h>
#include <SDL.h>

class KClock
{
public:
    // Initializes variables
    KClock();
    
    // Clock functions
    void start();
    void stop();
    
    void pause();
    void unpause();
    
    // Return clock's current time
    Uint32 getTicks();
    
    // Clock state getters
    bool isRunning();
    bool isPaused();
    
private:
    // Starting time
    Uint32 mStartingTicks;
    
    // Ticks at pause
    Uint32 mPauseTicks;
    
    // Clock states
    bool mRunning, mPaused;
};

#endif /* clock_hpp */
