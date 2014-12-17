//
//  Game.h
//  Tetris
//
//  Created by Matthew Houston on 7/26/14.
//  Copyright (c) 2014 mmhoust. All rights reserved.
//

#ifndef __MyGame__Game__
#define __MyGame__Game__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ResourcePath.hpp"
#include <vector>
#include <memory>
#include "Grid.h"


class Game {
public:
    Game();
    void run();
    void handleInputs();
    void update(sf::Time);
    void render();
    void reset();
private:
    sf::RenderWindow mWindow;
    Grid grid;
    sf::Font font;
};

#endif
