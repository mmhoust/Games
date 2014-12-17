
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Vector>
#include <iostream>
#include <pthread.h>

using namespace std;

#define spriteRows 3
#define spriteCols 7
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
		sf::Sound soundFire;
		sf::Sound soundExplosion;
	public:
		SoundEffects();
		void fireSound();
		void explosionSound();
};

class Sprites {

	enemyDir dir;
	SoundEffects sound;


	sf::Texture ship;
	sf::Font font;
	sf::Text gameOverText;
	sf::Texture enemy;
	sf::Texture exp;
	
	sf::Sprite shipSprite;
	sf::Sprite enemySprite[spriteRows*spriteCols*5];
	bool isDead[spriteRows*spriteCols*5];
	sf::RectangleShape bullet;
	sf::RectangleShape enemyBullet;
	bool isOver;
	bool isWon;

public:
	Sprites();
	void reset();
	void fireBullet();
	void drawAll(sf::RenderWindow*,float);
	void setExp();
	void detectCollision();
	void moveShip(float);
	void fireEnemyBullet(float);
	void moveBullet(float);
	void moveEnemy(float);
};