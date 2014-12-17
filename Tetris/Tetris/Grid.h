//
//  Grid.h
//  Tetris
//
//  Created by Matthew Houston on 7/26/14.
//  Copyright (c) 2014 mmhoust. All rights reserved.
//

#ifndef __Tetris__Grid__
#define __Tetris__Grid__

#include <iostream>
#include <Vector>
#include <memory>
#include "Block.h"
#define row 19
#define col 15

struct Shape {
    std::shared_ptr<Block> b1;
    std::shared_ptr<Block> b2;
    std::shared_ptr<Block> b3;
    std::shared_ptr<Block> b4;
};
enum  ShapeType {
    LINE,
    ZLEFT,
    ZRIGHT,
    LLEFT,
    LRIGHT,
    SQUARE,
    T
};

class Grid : public sf::Drawable , public sf::Transformable{
public:
    typedef std::vector<std::vector<std::unique_ptr<Block>>> gridArray;
private:
    std::shared_ptr<Block> grid[col][row];
    ShapeType shapeBuffer;
    Shape shape;
public:
    Grid();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    gridArray& getGrid();
    void update(sf::Time dt);
private:
    bool checklines();
    void moveActiveBlocks(int);
    void newShape();
    void moveShapeDown();
    Block getNextDownPos();
    bool collision();
};
#endif /* defined(__Tetris__Grid__) */
