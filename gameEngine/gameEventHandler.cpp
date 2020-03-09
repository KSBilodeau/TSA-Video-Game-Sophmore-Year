//
//  gameEventHandler.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 2/20/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#include "gameEventHandler.hpp"
#include "main.hpp"

GameEventHandler::GameEventHandler()
{
    events.clear();
}

GameEventHandler::~GameEventHandler()
{
    events.clear();
}

// I get this seems a little redundant seeing as both the constructor and destructor
// do the same thing as this, but having a manual option to clear events could be helpful later
void GameEventHandler::clearEventStorage()
{
    events.clear();
}

void GameEventHandler::removeEvent(int storageID)
{
    events.erase(storageID);
}

void GameEventHandler::removeEvent(int eventID, EventType event)
{
    bool itemFound = false;
    int removalIndex = 0;
    
    for (int i = 0; i < events.size(); i++)
    {
        if (events[i]->getType() == event && events[i]->eventID == eventID)
        {
            itemFound = true;
            removalIndex = i;
            break;
        }
    }
    
    if (itemFound)
        events.erase(removalIndex);
}

void GameEventHandler::handleTileCollisionEvent(int &storageID)
{
    if (((TileCollisionEvent*) events[storageID].get())->attachedEventType == EventType::textboxEvent)
        tileProcessor.triggerEvent(((TileCollisionEvent*) events[storageID].get())->attachedEventID);
}

void GameEventHandler::triggerEvent(int storageID, EventType eventType)
{
    if (eventType == EventType::textboxEvent)
        textboxProcessor.runTextboxSequence(((TextboxEvent*) (events.at(storageID).get()))->textboxGroupID);
    if (eventType == EventType::tileCollisionEvent)
        handleTileCollisionEvent(storageID);
}

std::map<int, std::shared_ptr<Event>> &GameEventHandler::getEvents()
{
    return events;
}
