//
//  clock.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/31/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#include "clock.hpp"

KClock::KClock()
{
    mStartingTicks = 0;
    mPauseTicks = 0;
    
    mRunning = false;
    mPaused = false;
}

void KClock::start()
{
    // Start the timer
    mRunning = true;
    
    // Unpause the time (if paused)
    mPaused = false;
    
    mStartingTicks = SDL_GetTicks();
    mPauseTicks = 0;
}

void KClock::stop()
{
    // Stop the timer
    mRunning = false;
    
    // Unpause the timer
    mPaused = false;
    
    // Clear the tick variables
    mStartingTicks = 0;
    mPauseTicks = 0;
}

void KClock::pause()
{
    // Check if the timer is running and not paused
    if (mRunning && !mPaused)
    {
        // Pause the timer
        mPaused = true;
        
        // Calculate the pause ticks
        mPauseTicks = SDL_GetTicks() - mStartingTicks;
        mStartingTicks = 0;
    }
}

void KClock::unpause()
{
    // Check if the timer is running and paused
    if (mRunning && mPaused)
    {
        // Unpause the timer
        mPaused = false;
        
        // Reset the starting ticks
        mStartingTicks = SDL_GetTicks() - mPauseTicks;
        
        // Reset the pause ticks
        mPauseTicks = 0;
    }
}

Uint32 KClock::getTicks()
{
    // The actual time
    Uint32 time = 0;
    
    // If the timer is running
    if (mRunning)
    {
        // If the timer is paused
        if (mPaused)
        {
            // Return the number of ticks paused
            time = mPauseTicks;
        }
        else
        {
            // Return the current time minus the starting time
            time = SDL_GetTicks() - mStartingTicks;
        }
    }
    
    return time;
}
