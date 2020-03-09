//
//  tileCollisionProcessor.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 3/2/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef tileCollisionProcessor_hpp
#define tileCollisionProcessor_hpp

#include "event.hpp"

#include <map>
#include <stdio.h>
#include <string>

class TileCollisionProcessor
{
public:
    // Initialize variables
    TileCollisionProcessor();
    
    // Deallocate variables
    ~TileCollisionProcessor();
    
    // Loads and processes linking file for tile collision events
    void loadEventsFromFile(std::string path);
    
    // Adds a premade event to the list
    void registerEvent(std::shared_ptr<TileCollisionEvent> &tileCollisionEvent, int &tileX, int &tileY);
    
    // Triggers tile collision event of a specific ID
    void triggerEvent(int eventID);
    
private:
    // Points to all the tile collision events in the game
    std::map<int, std::shared_ptr<TileCollisionEvent>> mEvents;
};

#endif /* tileCollisionProcessor_hpp */
