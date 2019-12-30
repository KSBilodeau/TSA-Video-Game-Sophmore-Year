//
//  main.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/30/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#ifndef main_hpp
#define main_hpp

// Basic screen dimensions for window setup
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

// Game scale factor for tile textures
const int SCALE_FACTOR = 3;

// Tile dimensions for future tilemap system
const int TILE_WIDTH = 16 * SCALE_FACTOR;
const int TILE_HEIGHT = 16 * SCALE_FACTOR;

// Main engine rendering window
extern SDL_Window* gWindow;

// Renderer for engine window
extern SDL_Renderer* gRenderer;

// Initializes libraries and game variables
bool init();

// Loads game media
bool loadMedia();

// Closes SDL subsystems and frees various things such as textures
void close();

#endif /* main_hpp */
