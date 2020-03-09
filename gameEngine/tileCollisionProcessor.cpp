//
//  tileCollisionProcessor.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 3/2/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#include "tileCollisionProcessor.hpp"
#include "main.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

TileCollisionProcessor::TileCollisionProcessor()
{
    mEvents.clear();
}

TileCollisionProcessor::~TileCollisionProcessor()
{
    mEvents.clear();
}

void TileCollisionProcessor::loadEventsFromFile(std::string path)
{
    // String that will hold each line
    std::string line;
    
    // Keeps track of line number
    int lineNum = 0;
    
    // File being read
    std::ifstream input;
    input.open(path);
    
    
    int tileX = 0, tileY = 0;
    int eventID = 0;
    
    // While there is another line in the file
    while (!input.eof())
    {
        getline(input, line);
        
        std::shared_ptr<Event> event;
        
        if (line.find("END") != std::string::npos)
            break;
        else if (line.find("TILE_POS") != std::string::npos)
        {
            std::istringstream iss(line);
            std::vector<std::string> charArray;
            std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(charArray));
            
            tileX = std::stoi(charArray[1]);
            tileY = std::stoi(charArray[2]);
        }
        else if (line.find("LINK_EVENT") != std::string::npos)
        {
            std::istringstream iss(line);
            std::vector<std::string> id;
            
            std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(id));
            
            eventID = std::stoi(id[1]);
        }
        else if (line.find("EVENT_TYPE") != std::string::npos)
        {
            if (line.find("TEXTBOX_SEQUENCE") != std::string::npos)
            {
                TileCollisionEvent event;
                event.attachedEventID = eventID;
                event.attachedEventType = EventType::textboxEvent;
                
                std::shared_ptr<TileCollisionEvent> temp = std::make_shared<TileCollisionEvent>(event);
                registerEvent(temp, tileX, tileY);
            }
        }
        
        lineNum++;
    }
}

void TileCollisionProcessor::registerEvent(std::shared_ptr<TileCollisionEvent> &tileCollisionEvent, int &tileX, int &tileY)
{
    mEvents.insert(std::make_pair(mEvents.size(), tileCollisionEvent));
    
    eventHandler.registerEvent(tileCollisionEvent);
    
    gMap.attachTileCollisionEvent(tileX, tileY, tileCollisionEvent->attachedEventID, tileCollisionEvent->eventID, tileCollisionEvent->attachedEventType);
}

void TileCollisionProcessor::triggerEvent(int eventID)
{
    textboxProcessor.runTextboxSequence(mEvents.find(eventID)->second->attachedEventID);
}
