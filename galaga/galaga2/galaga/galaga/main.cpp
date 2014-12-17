
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "galaga.hpp"

SoundEffects::SoundEffects(){
	if(!fire.loadFromFile("soundeffects/firing.wav")){
		perror("Unable to load file");
		exit(1);
	}
	if(!explosion.loadFromFile("soundeffects/explosion.wav")){
		perror("Unable to load file");
		exit(1);
	}
}
void SoundEffects::fireSound(){
	sound.setBuffer(fire);
	sound.play();
}
void SoundEffects::explosionSound(){
	sound.setBuffer(explosion);
	sound.play();
}


Sprites::Sprites() {
	
	if(!ship.loadFromFile("ship.png") ||
       !enemy.loadFromFile("enemy.jpg") ||
       !exp.loadFromFile("explosion.png")||
       !font.loadFromFile("Times.dfont")){
		perror("could not load files");
		exit(1);
	}
	shipSprite.setTexture(ship);
	shipSprite.setPosition(windowSizeX/2 -
                           shipSprite.getGlobalBounds().width,windowSizeY
                           -shipSprite.getGlobalBounds().height);
    
	for(int i = 0; i < spriteCols * spriteRows; i++){
		enemySprite[i].setTexture(enemy);
		isDead[i] = false;
	}
	for(int i =0; i < spriteCols; i++){
		enemySprite[i].setPosition((enemy.getSize().x+20)*i,100);
	}
	dir = RIGHT;
	bullet = sf::RectangleShape(sf::Vector2f(10,50));
	bullet.setFillColor(sf::Color::Red);
	bullet.setPosition(0,-50);
}

void Sprites::moveShip(float dt){
	sf::Vector2f pos = shipSprite.getPosition();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pos.x > 0){
		shipSprite.move(sf::Vector2f(-500*dt,0));
	}if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pos.x <
		(windowSizeX - shipSprite.getGlobalBounds().width)){
		shipSprite.move(sf::Vector2f(500*dt,0));
	}
}
void Sprites::moveEnemy(float dt){
	sf::Vector2f pos = enemySprite[0].getPosition();
	if(pos.x < 0 ){
		dir = RIGHT;
		for(int i = 0; i < spriteRows*spriteCols; i++){
			pos = enemySprite[i].getPosition();
			enemySprite[i].setPosition(pos.x, pos.y + enemy.getSize().y);
		}
	}
	else if(enemySprite[spriteCols-1].getPosition().x
            > windowSizeX - enemy.getSize().x){
		dir = LEFT;
        
		for(int i = 0; i < spriteRows*spriteCols; i++){
			pos = enemySprite[i].getPosition();
			enemySprite[i].setPosition(pos.x, pos.y + enemy.getSize().y);
		}
	}
	for(int i = 0; i < spriteRows * spriteCols; i++){
		pos = enemySprite[i].getPosition();
		if(dir == LEFT){
			enemySprite[i].setPosition(pos.x-100*dt, pos.y);
		}
		else if(dir == RIGHT){
			enemySprite[i].setPosition(pos.x+100*dt, pos.y);
		}
		cout << i << " " << pos.x << endl;
	}
}

void Sprites::moveBullet(float dt){
	bullet.move(sf::Vector2f(0,-500*dt));
}

void Sprites::fireBullet(){
	if(bullet.getPosition().y < 0){
		sf::Vector2f pos = shipSprite.getPosition();
		bullet.setPosition(pos.x+70,pos.y);
		sound.fireSound();
	}
}

void Sprites::detectCollision(){
	sf::FloatRect bulletBounds(bullet.getGlobalBounds());
	for(int i = 0; i < spriteRows* spriteCols; i++){
		if(bulletBounds.intersects(enemySprite[i].getGlobalBounds()) && !isDead[i]){
			isDead[i] = true;
			bullet.setPosition(0,-50);
		}
		if(shipSprite.getGlobalBounds().intersects(enemySprite[i].getGlobalBounds())){
			isOver = true;
			return;
		}
    }
    for(int i = 0;i<spriteRows*spriteCols; i++){
        if(!isDead[i]){
            return;
        }
    }
           isOver = true;
           }
           
           void Sprites::drawAll(sf::RenderWindow *window,float dt){
               if(!isOver){
                   window->draw(shipSprite);
                   window->draw(bullet);
                   for(int i = 0; i<spriteRows*spriteCols; i++){
                       if(!isDead[i]){
                           window->draw(enemySprite[i]);
                       }
                   }
               }else{
                   //game over scene
                   
               }
               window->display();
           }
           
           int main(){
               sf::RenderWindow window(sf::VideoMode(800,600), "Window");
               sf::Clock frameTime;
               window.setVerticalSyncEnabled(true);
               Sprites sprites;
               SoundEffects sounds;
               while (window.isOpen()){
                   
                   sf::Event event;
                   float dt = frameTime.restart().asSeconds();
                   window.clear(sf::Color::Black);
                   
                   while(window.pollEvent(event)){
                       
                       if(event.type == sf::Event::Closed){
                           window.close();
                       }
                       
                       else if(event.type == sf::Event::KeyPressed){
                           
                           if(event.key.code == sf::Keyboard::Space){
                               sprites.fireBullet();
                           } 	
                           
                           if(event.key.code == sf::Keyboard::Escape){
                               window.close();
                           }
                       }
                       
                   }
                   sprites.moveShip(dt);
                   sprites.moveBullet(dt);
                   sprites.moveEnemy(dt);
                   sprites.detectCollision();
                   sprites.drawAll(&window,dt);
                   
               }
               return 0;
           }