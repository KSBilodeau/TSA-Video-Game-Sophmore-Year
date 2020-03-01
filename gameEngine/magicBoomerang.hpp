//
//  magicBoomerang.hpp
//  gameEngine
//
//  Created by Keegan Bilodeau on 2/21/20.
//  Copyright © 2020 Keegan Bilodeau. All rights reserved.
//

#ifndef magicBoomerang_hpp
#define magicBoomerang_hpp

#include "gameObject.hpp"
#include "textureWrapper.hpp"

#include <stdio.h>

class KBoomerang : GameObject
{
public:
    // Initialize variables
    KBoomerang();
    
    // Deallocate variable
    ~KBoomerang();
    
    // Delete boomerang
    void free();
    
    // Create boomerang
    void createBoomerang(std::shared_ptr<KTexture> boomerangTexture);
};

#endif /* magicBoomerang_hpp */
