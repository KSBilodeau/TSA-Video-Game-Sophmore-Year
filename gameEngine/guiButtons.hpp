//
//  guiButtons.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/31/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#ifndef guiButtons_hpp
#define guiButtons_hpp

#include <stdio.h>

#include "gameObject.hpp"
#include "textureWrapper.hpp"
#include "sprite.hpp"

template<class Parent, class Return, class...Params>
struct MemberLambda
{
    // This variable stores a pointer to the parent class
    // TODO: FIND OUT WHY THIS IS NECCESSARY
    Parent* self;
    
    // This stores a pointer to the lambda that the "function" will use when called
    void (*lambda)(Parent * self, Params...);
    
    // Allows for default construction
    MemberLambda() = default;
    
    // This constructor assigns the parent class and lambda
    MemberLambda(Parent* self, void(*lambda)(Parent *self, Params...)) :
    self(self), lambda(lambda) {};
    
    // Overloads argument operator to call the lambda
    Return operator()(Params... p) const { return lambda(self, p...); };
    
    // This overloads the = operator so a lambda can be assigned to the struct
    void operator=(void (*lambda)(Parent* self, Params...))
    {
        this->lambda = lambda;
    };
};

class GUIButton : GameObject
{
public:
    // Pure virtual deconstructor
    virtual ~GUIButton() = 0;
    
    // Called by handle mouse click
    virtual void activate() = 0;
};

class MainMenuButton : GUIButton
{
public:
    // Initialize variable
    MainMenuButton();
    
    // Creates a gui button
    void createMainMenuButton(std::shared_ptr<KTexture> backgroundTexture, std::shared_ptr<KTexture> icon, int x, int y, SDL_Rect rects[2]);
    
    // Renders button to screen
    void render() override;
    
    // Updates button?
    void update(SDL_Event &event) override;
    
    // Frees everything maybe?
    void free() override;
    
    // Handles mouse clicks on button
    bool handleMouseClick(SDL_Event &event) override;
    
    // Does whatever this button is supposed to do
    void activate() override;
    
    // Creates a lambda "function" which takes in a bool reference as an arguement
    // In the case of most buttons, this bool will be isSelected
    MemberLambda<MainMenuButton, void, bool&> lambdaActivate = MemberLambda<MainMenuButton, void, bool&>(this, nullptr);
    
    // Toggle isSelected
    void toggleSelected();
    
    // Returns button's dimensions
    SDL_Rect& getRectangle() override;
    
    // Returns button state
    bool& getButtonState();
    
private:
    // Base texture
    std::shared_ptr<KTexture> mBackgroundTexture;
    
    // Icon texture
    std::shared_ptr<KTexture> mIcon;
    
    // Selection flag
    bool isSelected;
    
    // Buttons dimensions
    SDL_Rect mRectangle;
    
    // Texture clip rectangles
    SDL_Rect mClipRects[2];
};

#endif /* guiButtons_hpp */
