//
//  main.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/30/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "main.hpp"
#include "sprite.hpp"
#include "textureWrapper.hpp"
#include "textureHandler.hpp"
#include "guiButtons.hpp"
#include "clock.hpp"
#include "block.hpp"

SDL_Window* gWindow = nullptr;

SDL_Renderer* gRenderer = nullptr;

TTF_Font* gFont = nullptr;

Mix_Music* gIntroMusic = nullptr;

Player gPlayer;

KMap gMap;

TextureRegister textureRegistry;

KTilesheet tiles;

SDL_Rect camera;

std::pair<int, int> selectedTileID;

bool init()
{
    // Initialization success flag
    bool success = true;
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    // If SDL successfully initialized
    else
    {
        // Creates a visible window
        gWindow = SDL_CreateWindow("My Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        // If window could be created
        else
        {
            // Create renderer with hardware acceleration and V-Sync enabled
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == nullptr)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            // If renderer could be created
            else
            {
                // Initialize draw color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
                // Initialize image loading (specifically pngs; however, more can be added)
                int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                
                // Initialize SDL mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                
                // Initalize font loading for future text rendering
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }
    
    return success;
}

// TODO: Add non-manual way of importing files
bool loadMedia()
{
    // Media import success flag
    bool success = true;
    
    KTexture testTexture;
    if (!testTexture.loadFromFile("background.png", 1))
    {
        printf("Test texture could not be loaded!\n");
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(0, testTexture);
    }
    
    if (!testTexture.loadFromFile("sprites.png", 1))
    {
        printf("Test texture could not be loaded!\n");
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(1, testTexture);
    }
    
    if (!testTexture.loadFromFile("redSheet.png", 1))
    {
        printf("Test texture could not be loaded!\n");
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(2, testTexture);
    }

    if (!testTexture.loadFromFile("save.png", .9))
    {
        printf("Test texture could not be loaded!\n");
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(3, testTexture);
    }
    
    if (!testTexture.loadFromFile("Tiles1.png", 3))
    {
        printf("Test texture could not be loaded!\n");
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(4, testTexture);
    }
    
    if (!testTexture.loadFromFile("Player.jpg", 3))
    {
        printf("Player texure could not be loaded!\n");
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(5, testTexture);
    }
    
    gIntroMusic = Mix_LoadMUS("Game_Music.wav");
    if (gIntroMusic == nullptr)
    {
        printf("Music could not be loaded!\n");
        success = false;
    }
    
    return success;
}

void close()
{
    // Free all textures that have not already been freed
    textureRegistry.freeAll();
}

int main(int argc, const char * argv[])
{
    // Main loop flag
    bool isRunning = true;
    
    // Event handler
    SDL_Event event;
    
    // Fps ticks
    KClock fpsTimer;
    
    // FPS cap timer
    KClock capTimer;
    
    // Games average FPS
    float avgFPS;
    
    try
    {
        if (!init())
            printf("Failed to initialize!\n");
        else if (!loadMedia())
            printf("Failed to load media!\n");
        
        camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        
        Sprite sprite;
        SDL_Rect rect {0, 0, 100, 100};
        sprite.createSprite(0, rect, true);
        
        SDL_Rect startingRect {0, 0, 20 * SCALE_FACTOR, 26 * SCALE_FACTOR};
        gPlayer.createPlayer(textureRegistry.requestAccess(5), 20, 26, startingRect);
        
        int countedFrames = 0;
        fpsTimer.start();
        
        SDL_Rect buttonClipRect1 {339, 98, 49, 49};
        SDL_Rect buttonClipRect2 {290, 98, 49, 45};
        SDL_Rect rects[2] {buttonClipRect1, buttonClipRect2};
        
        MainMenuButton button;
        button.createMainMenuButton(textureRegistry.requestAccess(2), textureRegistry.requestAccess(3), 0, 0, rects);

        button.lambdaActivate = [](MainMenuButton *self, bool &isSelected) { isSelected = !isSelected; };
        
        tiles.loadFromTexture(4, 16, 16);
        
        KBlock block;
        block.loadDefaultTile(tiles.requestAccess(std::make_pair(0, 1)));
        block.setBlockPosition(0, 0);
        
//        ArrowKeys arrKeys;
        
        gMap.loadMap();
        
        while (isRunning)
        {
            capTimer.start();
            
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    isRunning = false;
                
                if (event.type == SDL_MOUSEBUTTONDOWN)
                    button.handleMouseClick(event);
                else if (event.type == SDL_MOUSEBUTTONUP && !button.handleMouseClick(event))
                    button.lambdaActivate(button.getButtonState());
                else
                    block.handleMouseClick(event);
            
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
                    Mix_PlayMusic(gIntroMusic, 1);
                
                gPlayer.update(event);
                gMap.update(event);
            }
            
            avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.0f);
            if (avgFPS > 2000000)
                avgFPS = 0;
            
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            
//            block.render();
            gMap.render();
            button.render();
                        
            gPlayer.move();
            gPlayer.render();
            
            SDL_RenderPresent(gRenderer);
            SDL_RenderClear(gRenderer);
            
            countedFrames++;
            
            int frameTicks = capTimer.getTicks();
            if (frameTicks < 1000 / 61)
                SDL_Delay((1000 / 61) - frameTicks);
            
            std::cout << avgFPS << '\n';
        }
    }
    catch (TextureAccessException e)
    {
        std::cout << e.what() << "\n";
    }
    
    close();
    return 0;
}
