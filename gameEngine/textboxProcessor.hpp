//
//  textboxProcessor.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 2/27/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef textboxProcessor_hpp
#define textboxProcessor_hpp

#include <map>
#include <stdio.h>
#include <string>
#include <vector>

#include "textbox.hpp"

struct TextboxSequence
{
    TextboxSequence(int id, int defID, int numBoxes)
    {
        sequenceID = id;
        currentTextboxID = defID;
        numOfTextboxes = numBoxes;
        
        complete = false;
    }
    
    // Completion flag
    bool complete;
    
    // Identifies this individual sequence
    int sequenceID;
    
    // The id of the currently displayed textbox
    int currentTextboxID;
    
    // Stores the number of textboxes
    int numOfTextboxes;
    
    // All the textboxes in the textbox sequence
    std::vector<std::shared_ptr<Textbox>> textboxes;
    
    // Renders the current texture
    void render()
    {
        textboxes[currentTextboxID]->render();
    }
    
    // Increments the current texure flag
    void increment()
    {
        if (currentTextboxID < numOfTextboxes - 1)
        {
            currentTextboxID++;
        }
        else
            complete = true;
    }
    
    // Decrements the current texture flag
    void decrement()
    {
        if (currentTextboxID > 0)
            currentTextboxID--;
    }
    
    void attachTextbox(std::vector<std::shared_ptr<Textbox>> &textbox)
    {
        textboxes = textbox;
    }
    
    std::shared_ptr<Textbox> &getCurrentTextbox()
    {
        return textboxes[currentTextboxID];
    }
};

class TextboxEventProcessor
{
public:
    // Initialize variables
    TextboxEventProcessor();
    
    // Deallocate variables
    ~TextboxEventProcessor();
    
    // Loads a sequence of textboxes from a file
    bool loadTextboxSequenceFromFile(std::string path);
    
    // Loads all sequences contained in a file (if there are more than one sequence)
    bool loadAllSequencesFromFile(std::string path);
    
    // Creates a textbox event
    void createTextboxEvent(std::vector<int> textboxIDs);
    
    // Adds textbox to map
    void registerTextboxSequence(std::shared_ptr<TextboxSequence> &textbox);
    
    // Runs a sequence of textboxes
    void runTextboxSequence(int sequenceID);
    
    // Updates the textbox and handles mousclicks
    bool updateCurrentEvent(SDL_Event &event);
    
    // Renders whatever current sequence is set to
    void renderCurrentEvent();
    
private:
    // Points to the active textbox sequence
    // Is set to nullptr once complete
    std::shared_ptr<TextboxSequence> currentSequence;
    
    // Stores all of the textbox sequences
    std::map<int, std::shared_ptr<TextboxSequence>> textboxSequences;
};

#endif /* textboxProcessor_hpp */
