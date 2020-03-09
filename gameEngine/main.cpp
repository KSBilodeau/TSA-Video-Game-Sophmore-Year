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
#include <cmath>

#include "main.hpp"
#include "event.hpp"
#include "textboxProcessor.hpp"
#include "gameEventHandler.hpp"
#include "sprite.hpp"
#include "textureWrapper.hpp"
#include "textureHandler.hpp"
#include "textbox.hpp"
#include "guiButtons.hpp"
#include "clock.hpp"
#include "block.hpp"
#include "keyHandler.hpp"

SDL_Window* gWindow = nullptr;

SDL_Renderer* gRenderer = nullptr;

TTF_Font* gFont = nullptr;

Mix_Music* gIntroMusic = nullptr;

KeyHandler keyHanlder;

GameEventHandler eventHandler;
TextboxEventProcessor textboxProcessor;
TileCollisionProcessor tileProcessor;

Player gPlayer;

KMap gMap;

TextureRegister textureRegistry;

KTilesheet tiles;

SDL_Rect camera;

std::pair<int, int> selectedTileID {6, 2};

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
                
                // Start the key handler
                keyHanlder.startKeyHandler();
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
    
    // Load fonts, music, etc...
    gFont = TTF_OpenFont("DejaVuSans.ttf", 20);
    if (gFont == nullptr)
    {
        printf("Game's font could not be loaded! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    
    gIntroMusic = Mix_LoadMUS("Game_Music.wav");
    if (gIntroMusic == nullptr)
    {
        printf("Music could not be loaded! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    
    // Load images, videos, etc...
    KTexture testTexture;
    if (!testTexture.loadFromFile("background.png", 1))
    {
        printf("Test texture could not be loaded! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(0, testTexture);
    }
    
    if (!testTexture.loadFromFile("sprites.png", 1))
    {
        printf("Test texture could not be loaded! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(1, testTexture);
    }
    
    if (!testTexture.loadFromFile("redSheet.png", 1))
    {
        printf("Test texture could not be loaded! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(2, testTexture);
    }

    if (!testTexture.loadFromFile("save.png", .9))
    {
        printf("Test texture could not be loaded! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(3, testTexture);
    }
    
    if (!testTexture.loadFromFile("Tiles1-1.png", 3))
    {
        printf("Test texture could not be loaded! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(4, testTexture);
    }
    
    if (!testTexture.loadFromFile("Player.jpg", 3))
    {
        printf("Player texure could not be loaded! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(5, testTexture);
    }
    
    if (!testTexture.loadFromFile("TextBox.png", 1.776))
    {
        printf("Textbox texture could not be loaded! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }
    else
    {
        textureRegistry.registerTexture(6, testTexture);
    }
    
    SDL_Color color {0xFF, 0xFF, 0xFF, 0xFF};
    if (!testTexture.loadFromString("Be wary of those who may bear light / For their souls may not be bright / Do not fight others out of spite / For it feeds the darkness\u0027 might", color))
    {
        printf("Text could not be loaded! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }
    else
        textureRegistry.registerTexture(7, testTexture);
    
    return success;
}

void close()
{
    // Free all textures that have not already been freed
    textureRegistry.freeAll();
    
    // Destroy font
    TTF_CloseFont(gFont);
    
    // Free music
    Mix_FreeMusic(gIntroMusic);
    Mix_CloseAudio();
    
    // Free renderer
    SDL_DestroyRenderer(gRenderer);
    // Free window
    SDL_DestroyWindow(gWindow);
    
    // Set all pointers back to null
    gWindow = nullptr;
    gRenderer = nullptr;
    gFont = nullptr;
    gIntroMusic = nullptr;
    
    // Close SDL subsystems
    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
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
        
        gMap.loadMap();
        
        Textbox textbox;
        textbox.createTextbox(textureRegistry.requestAccess(6), textureRegistry.requestAccess(7), (SCREEN_WIDTH / 2) - (textureRegistry.requestAccess(6)->getWidth() * 1.776 / 2), (SCREEN_HEIGHT / 1.20) - (textureRegistry.requestAccess(6)->getHeight() * 1.776 / 2));
        
        textboxProcessor.loadTextboxSequenceFromFile("textboxSequences.txt");
        textboxProcessor.loadTextboxSequenceFromFile("textboxSequences2.txt");
//        textboxProcessor.runTextboxSequence(0);
//        eventHandler.triggerEvent(0, EventType::textboxEvent);
        
        tileProcessor.loadEventsFromFile("specialTileCollisions.txt");
        tileProcessor.loadEventsFromFile("specialTileCollisions2.txt");
            
        SDL_Rect test {0, 0, 30, 30};
        SDL_Texture* texture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 30, 30);
        SDL_SetRenderTarget(gRenderer, texture);
        SDL_RenderDrawRect(gRenderer, &test);
        SDL_SetRenderTarget(gRenderer, NULL);
        
        test.x = 375;
        test.y = 375;
        
        int speed = 1;
        int angle = 60;
        int direction = 1;
        double degrees = 0;
        SDL_Point point;
        point.x = test.w / 2;
        point.y = test.h / 2;
        
        while (isRunning)
        {
            capTimer.start();
            
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    isRunning = false;
                
                if (event.type == SDL_KEYDOWN)
                {
                    if (keyHanlder.queryKeyState(SDL_SCANCODE_P))
                        Mix_PlayMusic(gIntroMusic, 1);
                }
                
                if (event.type == SDL_MOUSEBUTTONDOWN)
                    button.handleMouseClick(event);
                else if (event.type == SDL_MOUSEBUTTONUP && !button.handleMouseClick(event))
                    button.lambdaActivate(button.getButtonState());
                
                gPlayer.update(event);
                
                if (!textboxProcessor.updateCurrentEvent(event))
                    gMap.update(event);
            }
            
//            int x, y;
//            SDL_GetMouseState(&x, &y);
//
//            std::string mousePos = std::string("mouseX: " + std::to_string((int) std::floor(((double) (x + camera.y)) / 48.0)) + " mouseY: " + std::to_string((int) std::floor(((double) (y + camera.y)) / 48.0)));
//
//            SDL_Color black {0x00, 0x00, 0x00, 0xFF};
//            SDL_Surface* mouse = TTF_RenderText_Solid(gFont, mousePos.c_str(), black);
//            SDL_Texture* mouseTex = SDL_CreateTextureFromSurface(gRenderer, mouse);
            
            avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.0f);
            if (avgFPS > 2000000)
                avgFPS = 0;
            
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            
            gMap.render();
            button.render();
                        
            gPlayer.move();
            gPlayer.render();
            
//            textbox.render();
            textboxProcessor.renderCurrentEvent();
//            textureRegistry.requestAccess(8)->render(0, 0, true);
                        
//            SDL_Rect rect {SCREEN_WIDTH - 202, 0, 200, 50};
//            SDL_RenderCopy(gRenderer, mouseTex, NULL, &rect);
        
            if ((test.x > 750 || test.y > 750) || (test.x < 0 || test.y < 0))
                direction *= -1;
            test.x += direction * std::ceil((double) (speed * std::cos((angle * (M_PI / 180)))));
            test.y += direction * std::ceil((double) (speed * std::sin((angle * (M_PI / 180)))));
            SDL_RenderCopyEx(gRenderer, texture, NULL, &test, degrees, &point, SDL_FLIP_NONE);
            
            SDL_RenderPresent(gRenderer);
            SDL_RenderClear(gRenderer);
            
            countedFrames++;
            
            int frameTicks = capTimer.getTicks();
            if (frameTicks < 1000 / 61)
                SDL_Delay((1000 / 61) - frameTicks);
            
//            std::cout << avgFPS << '\n';
            degrees += 4;
        }
    }
    catch (TextureAccessException e)
    {
        std::cout << e.what() << "\n";
    }
    
    close();
    
//    GameEventHandler eventHandler;
//
//    std::shared_ptr<OneTimeEvent> event = std::make_shared<OneTimeEvent>();
//    event->eventID = 0;
//
//    std::shared_ptr<MultiTriggerEvent> event2 = std::make_shared<MultiTriggerEvent>();
//    event2->eventID = 0;
//    event2->infininteRepeat = true;
//
//    eventHandler.registerEvent<OneTimeEvent>(event);
//    eventHandler.registerEvent<MultiTriggerEvent>(event2);
//
//    for (std::pair<int, std::shared_ptr<Event>> mappedEvent : eventHandler.getEvents())
//        printf("storageID: %i  defaultEventType: %i  pointerType: %i\n", mappedEvent.first, EventType::event, mappedEvent.second->getType());
    
    return 0;
}
