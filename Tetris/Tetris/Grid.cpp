//
//  Grid.cpp
//  Tetris
//
//  Created by Matthew Houston on 7/26/14.
//  Copyright (c) 2014 mmhoust. All rights reserved.
//

#include "Grid.h"

Grid::Grid(){
    for (int i = 0; i<col; ++i){
        for (int j = 0; j < row; ++j){
            std::unique_ptr<Block> block(new Block(i,j));
            grid[i][j] =std::move(block);
        }
    }
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for (int i =0; i < col; ++i){
        for (int j = 0; j < row; ++j){
            target.draw(*grid[i][j]);
        }
    }
}

bool Grid::checklines(){
    // check and remove lines
    bool finalResult = false;
    bool result;
    for (int i = 0; i < col; ++i) {
        result = true;
        for (int j = 0; j < row; ++j) {
            if (!grid[i][j]->isActiveBlock()) {
                result = false;
            }
        }
        if (result){
            for (int j = 0; j < row; ++j) {
                grid[i][j]->resetBlock();
                moveActiveBlocks(i);
            }
            finalResult = true;
        }
    }
    return finalResult;
}

void Grid::moveActiveBlocks(int r){
    // move all blocks above new line down one
    for (int i = r; i > 0; --i) {
        for (int j = 0; j < row; ++j) {
            if (grid[i][j]->isActiveBlock()) {
                grid[i+1][j]->setActive(grid[i][j]->getColor());
            }else{
                grid[i+1][j]->resetBlock();
            }
        }
    }
}

void Grid::update(sf::Time dt){
    checklines();
    if (collision()) {
        newShape();
    }
    moveShapeDown();
}



