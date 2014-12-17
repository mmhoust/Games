//
//  Block.h
//  Tetris
//
//  Created by Matthew Houston on 7/26/14.
//  Copyright (c) 2014 mmhoust. All rights reserved.
//

#ifndef __Tetris__Block__
#define __Tetris__Block__

#include <iostream>
#include <SFML/Graphics.hpp>

class Block : public sf::Drawable, sf::Transformable{
private:
    sf::RectangleShape block;
    bool isActive;
public:
    Block(int, int);
    bool isActiveBlock();
    void resetBlock();
    void setActive(const sf::Color);
    sf::RectangleShape getBlock();
    sf::Color getColor();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
};
#endif /* defined(__Tetris__Block__) */
