//
//  Block.cpp
//  Tetris
//
//  Created by Matthew Houston on 7/26/14.
//  Copyright (c) 2014 mmhoust. All rights reserved.
//

#include "Block.h"

Block::Block(int i,int j):block(sf::Vector2f(24,24)){
    block.setPosition(25*i, 25*j);
    block.setFillColor(sf::Color::White);
    block.setOutlineColor(sf::Color::White);
    block.setOutlineThickness(1.f);
    isActive = false;
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(block);
}

bool Block::isActiveBlock(){
    return isActive;
}
void Block::setActive(const sf::Color color){
    isActive = true;
    block.setFillColor(color);
    block.setOutlineColor(sf::Color::Black);
}
void Block::resetBlock(){
    isActive = false;
    block.setFillColor(sf::Color::White);
    block.setOutlineColor(sf::Color::White);
}
sf::RectangleShape Block::getBlock(){
    return block;
}

sf::Color Block::getColor(){
    return block.getFillColor();
}

