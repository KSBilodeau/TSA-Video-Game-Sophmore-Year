//
//  event.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 2/25/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef event_h
#define event_h

enum EventType
{
    event,
    oneTimeEvent,
    multiTriggerEvent,
    textboxEvent,
    multiTriggerTexboxEvent,
    tileCollisionEvent,
    multiTriggerTileCollisionEvent
};

// Base event type from which all other events inherit from
typedef struct Event
{
    // Constructor required for make_shared
    Event()
    {
        eventID = 0;
    }
    
    // Event identifier
    int eventID;
    
    // Returns the enum for its type
    virtual EventType getType()
    {
        return EventType::event;
    }
} Event;


// Should be self explanatory, but just in case:
// This struct is used to represent a game event (tile interactions, one-time NPC dialog, etc)
// that will only be triggered once
typedef struct OneTimeEvent : Event
{
    // Constructor required for make_shared
    OneTimeEvent()
    {
        eventID = 0;
        triggered = false;
    }
    
    // Indicates if the event has been previously triggered
    bool triggered;
    
    // Returns the enum for its type
    EventType getType() override
    {
        return EventType::oneTimeEvent;
    }
} OneTimeEvent;

// Should also be self explanatory, but just in case:
// This struct is used to represent a game event (NPC interactions, weapon use, etc)
// that will be triggered either a certain # of times or an infinite # of times
typedef struct MultiTriggerEvent : Event
{
    // Constructor required for make_shared
    MultiTriggerEvent()
    {
        eventID = 0;
        numOfRepeats = 0;
        numOfTriggers = 0;
        
        infininteRepeat = false;
    }
    
    // If infiniteRepeat == false:
    // This variable indicates the number of times this event can be triggered
    int numOfRepeats;
    // This variable indicates the number of times this event has been previously triggered
    int numOfTriggers;
    
    // Flag indicating that this event can be repeated infinitely
    bool infininteRepeat;
    
    // Returns the enum of its type
    EventType getType() override
    {
        return EventType::multiTriggerEvent;
    }
} MultiTriggerEvent;

// TODO: FOR NATIONALS ADD PERSONALIZATION TO TEXT BOXES
// TODO: AKA DIFFERENT COLORED BOXES FOR EACH CHARACTER OR MAYBE PORTRAITS?
// This struct will notify the textbox handler to display a series of textboxes based of
// the events id
typedef struct TextboxEvent : OneTimeEvent
{
    // Constructor required for make_shared
    TextboxEvent() : OneTimeEvent()
    {
        textboxGroupID = 0;
    }
    
    // Textbox handler identifier (INDICATES WHICH SERIES OF TEXTBOXES TO DISPLAY (USED BY
    // textboxHandler.cpp && textboxHandler.hpp))
    int textboxGroupID;
    
    // Returns the enum of its type
    EventType getType() override
    {
        return  EventType::textboxEvent;
    }
} TextboxEvent;

typedef struct MultiTriggerTextboxEvent : MultiTriggerEvent
{
    // Make shared requires a constructor
    MultiTriggerTextboxEvent() : MultiTriggerEvent()
    {
        textboxGroupID = 0;
    }
    
    // Indicates which series of texboxes to trigger
    int textboxGroupID;
    
    // Returns the enum of its type
    EventType getType() override
    {
        return EventType::multiTriggerTexboxEvent;
    }
} MultiTriggerTextboxEvent;

typedef struct TileCollisionEvent : OneTimeEvent
{
    TileCollisionEvent() : OneTimeEvent()
    {
        attachedEventID = 0;
    }
    
    // Storage ID of the event attached
    int attachedEventID;
    
    // Type of the attached event
    EventType attachedEventType;
    
    EventType getType() override
    {
        return EventType::tileCollisionEvent;
    }
    
} TileCollisionEvent;

typedef struct MultiTriggerTileCollisionEvent : MultiTriggerEvent
{
    
} MultiTriggerTileCollisionEvent;

#endif /* event_h */
