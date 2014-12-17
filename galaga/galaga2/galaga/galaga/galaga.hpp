//
//  galaga.hpp
//  galaga
//
//  Created by Matthew Houston on 7/7/14.
//  Copyright (c) 2014 mmhoust. All rights reserved.
//

#ifndef galaga_galaga_hpp
#define galaga_galaga_hpp

#include <Vector>
#include <iostream>
#include <pthread.h>

using namespace std;

#define spriteRows 1
#define spriteCols 4
#define spacing 75
#define windowSizeX 800
#define windowSizeY 600

typedef enum enemyDir{
	LEFT,
	RIGHT,
	DOWN,
	UP,
} enemyDir;


class SoundEffects {
    sf::SoundBuffer fire;
    sf::SoundBuffer explosion;
    sf::Sound sound;
public:
    SoundEffects();
    void fireSound();
    void explosionSound();
};

class Sprites {
	int enemyHitCount;
	enemyDir dir;
    
	SoundEffects sound;
    
	sf::Texture ship;
	sf::Font font;
	sf::Texture enemy;
	sf::Texture exp;
	sf::Sprite shipSprite;
	sf::Sprite enemySprite[spriteRows*spriteCols];
	bool isDead[spriteRows*spriteCols];
	sf::RectangleShape bullet;
	bool isOver;
    
public:
	Sprites();
	void fireBullet();
	void drawAll(sf::RenderWindow*,float);
	void setExp();
	void detectCollision();
	void moveShip(float);
	void moveBullet(float);
	void moveEnemy(float);
};

#endif
