//
//  eventHandler.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 2/20/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#include "keyHandler.hpp"

KeyHandler::KeyHandler()
{
    keyboardStates = nullptr;
}

KeyHandler::~KeyHandler()
{
    keyboardStates = nullptr;
}

void KeyHandler::startKeyHandler()
{
    keyboardStates = SDL_GetKeyboardState(NULL);
}

bool KeyHandler::queryKeyState(SDL_Keycode keyCode)
{
    keyboardStates = SDL_GetKeyboardState(NULL);
    return keyboardStates[keyCode];
}
