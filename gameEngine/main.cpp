//
//  main.cpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 12/30/19.
//  Copyright © 2019 Keegan Bilodeau. All rights reserved.
//

#include <iostream>
#include <SDL.h>

int main(int argc, const char * argv[]) {
    SDL_Rect rect {0, 0, 100, 100};
    printf("x: %i\n", rect.x);
    return 0;
}
