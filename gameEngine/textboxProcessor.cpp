//
//  textboxProcessor.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 2/27/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#include "textboxProcessor.hpp"
#include "main.hpp"

#include <fstream>

TextboxEventProcessor::TextboxEventProcessor()
{
    currentSequence = nullptr;
    
    textboxSequences.clear();
}

TextboxEventProcessor::~TextboxEventProcessor()
{
    textboxSequences.clear();
}

void TextboxEventProcessor::registerTextbox(std::shared_ptr<TextboxSequence> &textbox)
{
    textboxSequences.insert(std::make_pair(textboxSequences.size(), textbox));
}

bool TextboxEventProcessor::loadTextboxSequenceFromFile(std::string path)
{
    // Loading success flag
    bool success = true;
    
    // String that will hold each line
    std::string line;
    
    // Keeps track of line number
    int lineNum = 0;
    
    // File being read
    std::ifstream input;
    input.open(path);
    
    std::vector<std::shared_ptr<Textbox>> textboxes;
    
    TextboxSequence sequence (static_cast<int>(textboxSequences.size()), 0, static_cast<int>(textboxes.size()));
    std::shared_ptr<TextboxSequence> sequencePtr = std::make_shared<TextboxSequence>(sequence);
    
    // While there is another line in the file
    while (!input.eof())
    {
        getline(input, line);
        
        if (line.compare(((std::string) ("SEQUENCE END " + line))) == 0)
            break;
        if (line.find('\"') != std::string::npos)
        {
            line.erase(std::remove(line.begin(), line.end(), '\"'), line.end());
            
            KTexture temp;
            temp.loadFromString(line, {0, 0, 0});
            textureRegistry.registerTexture(8 + (lineNum - 1), temp);
            
            Textbox textbox;
            textbox.createTextbox(textureRegistry.requestAccess(6), textureRegistry.requestAccess(8 + lineNum - 1), (SCREEN_WIDTH / 2) - (textureRegistry.requestAccess(6)->getWidth() * 1.776 / 2), (SCREEN_HEIGHT / 1.20) - (textureRegistry.requestAccess(6)->getHeight() * 1.776 / 2));
            
            std::shared_ptr<Textbox> temp2 = std::make_shared<Textbox>(textbox);
            textboxes.push_back(temp2);
        }
        
        lineNum++;
    }
    
    if (success)
    {
        sequencePtr->numOfTextboxes = (int) textboxes.size();
        sequencePtr->attachTextbox(textboxes);
        registerTextbox(sequencePtr);
    }
    
    return success;
}

bool TextboxEventProcessor::loadAllSequencesFromFile(std::string path)
{
    // Loading success flag
    bool success = true;
    
    return success;
}

void TextboxEventProcessor::updateCurrentEvent(SDL_Event &event)
{
    if (currentSequence != nullptr)
    {
        bool check = currentSequence->getCurrentTextbox()->handleMouseClick(event);
        
        if (check)
            currentSequence->increment();
    }
}

void TextboxEventProcessor::renderCurrentEvent()
{
    if (currentSequence != nullptr)
    {
        if (!currentSequence->complete)
            currentSequence->render();
    }
}

void TextboxEventProcessor::runTextboxSequence(int sequenceID)
{
    if (currentSequence == nullptr)
    {
        if (!textboxSequences[sequenceID]->complete)
            currentSequence = textboxSequences[sequenceID];
    }
    else
    {
        currentSequence = nullptr;
    }
}
