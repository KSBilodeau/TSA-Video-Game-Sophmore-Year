//
//  main.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/30/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#ifndef main_hpp
#define main_hpp

#include <SDL_ttf.h>

#include "textureHandler.hpp"
#include "tile.hpp"
#include "player.hpp"
#include "map.hpp"

struct ArrowKeys
{
    int convertToReasonableValue(SDL_Keycode key)
    {
        if (key == SDLK_UP)
            return 128;
        else if (key == SDLK_DOWN)
            return 129;
        else if (key == SDLK_LEFT)
            return 130;
        else if (key == SDLK_RIGHT)
            return 131;
        else
            return -1;
    }
};

// Basic screen dimensions for window setup
const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 750;

// Game scale factor for tile textures
const int SCALE_FACTOR = 3;

// Block dimensions for future tilemap system
const int BLOCK_WIDTH = 12;
const int BLOCK_HEIGHT = 12;

// Tile dimensions for future tilemap system
const int TILE_WIDTH = 16 * SCALE_FACTOR;
const int TILE_HEIGHT = 16 * SCALE_FACTOR;

extern KTile gTile;

// Main engine rendering window
extern SDL_Window* gWindow;

// Renderer for engine window
extern SDL_Renderer* gRenderer;

// Global font that will be used for the game
extern TTF_Font* gFont;

// Game's player
extern Player gPlayer;

// Game's map
extern KMap gMap;

// Handles textures for the whole game
extern TextureRegister textureRegistry;

// Handles tiles for the whole game
extern KTilesheet tiles;

// The games camera rectangle
extern SDL_Rect camera;

// Tile ID of the currently selected tile
extern std::pair<int, int> selectedTileID;

// Initializes libraries and game variables
bool init();

// Loads game media
bool loadMedia();

// Closes SDL subsystems and frees various things such as textures
void close();

#endif /* main_hpp */
