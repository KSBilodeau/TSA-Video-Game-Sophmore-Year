//
//  gameEventHandler.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 2/20/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef gameEventHandler_hpp
#define gameEventHandler_hpp

#include "textureWrapper.hpp"
#include "event.hpp"

#include <map>
#include <stdio.h>
#include <vector>

// DISCLAIMER: All event structs are in event.hpp so that other classes can access and use them

/*
    This class maintains the storage and "triggering" of in-game events (actual event processing
    is handled by more specialized classes like textbox handler)
 
    Think of this as a hub between the gameObjects and the game's predefined events:
    ( "=>" indicates a passing of data to another class)
 
    Player collides with a specific tile =>
    Map detects the collision and discovers an event ID linked to it =>
    GameEventHandler finds a textbox sequence event with that id so it sends it to it
    specialized processing class =>
    Textbox handler triggers the displaying of a specific series of textboxes as indicated by
    the event id
*/
class GameEventHandler
{
public:
    // Initialize variables
    GameEventHandler();
    
    // Deallocate variables
    ~GameEventHandler();
    
    // Manually clears all events without destroying the whole object
    void clearEventStorage();
    
    // Removes an event using its storage ID (not the event id which is used by the classes that
    // actually process the event in game)
    void removeEvent(int storageID);
    
    // If for some reason storageID is impossible to know, this more expensive function will
    // remove events using its eventID
    void removeEvent(int eventID, EventType event);
    
    // Adds event to list
    template<typename E>
    void registerEvent(std::shared_ptr<E> &e)
    {
        ((std::shared_ptr<Event>) e)->eventID = (int) events.size();
        events.insert(std::make_pair(events.size(), e));
    }
    
    // Handles event triggers
    void triggerEvent(int storageID, EventType eventType);
    
    // Special function for handling tile collision events
    void handleTileCollisionEvent(int &storageID);
    
    std::map<int, std::shared_ptr<Event>> &getEvents();
    
private:
    // This map contains all events for the game
    // Events are ordered storage ID (used by gameEventHandler) as pointers in order to retain
    // The possible children classes typing and event ID
    std::map<int, std::shared_ptr<Event>> events;
};


#endif /* gameEventHandler_hpp */
