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
	soundFire.setBuffer(fire);
	soundFire.play();
}
void SoundEffects::explosionSound(){
	soundExplosion.setBuffer(explosion);
	soundExplosion.play();
}


Sprites::Sprites() {
	
	if(!ship.loadFromFile("sprites/ship.png") || 
		!enemy.loadFromFile("sprites/enemy.jpg") ||
		!exp.loadFromFile("sprites/explosion.png")||
		!font.loadFromFile("sprites/Times.dfont")){
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
	
	for (int j= 0; j < spriteRows; j++){
		for(int i =0; i < spriteCols; i++){
			enemySprite[i+j*spriteCols].setPosition(
				(enemy.getSize().x+20)*i,20+enemy.getSize().y*j);
		}
	}
	
	dir = RIGHT;
	bullet = sf::RectangleShape(sf::Vector2f(10,50));
	bullet.setFillColor(sf::Color::Red);
	bullet.setPosition(0,-50);

	enemyBullet = sf::RectangleShape(sf::Vector2f(10,50));
	enemyBullet.setFillColor(sf::Color::Blue);
	enemyBullet.setPosition(0,-50);


}

void Sprites::reset(){
	shipSprite.setPosition(windowSizeX/2 - 
		shipSprite.getGlobalBounds().width,windowSizeY
		-shipSprite.getGlobalBounds().height);

	for(int i = 0; i < spriteCols * spriteRows; i++){
		isDead[i] = false;
	}	

	for (int j= 0; j < spriteRows; j++){
		for(int i =0; i < spriteCols; i++){
			enemySprite[i+j*spriteCols].setPosition(
				(enemy.getSize().x+20)*i,20+enemy.getSize().y*j);
		}
	}

	bullet.setPosition(0,-50);
	enemyBullet.setPosition(0,700);
	dir = RIGHT;
	isOver = false;
	isWon = false;
}

void Sprites::moveShip(float dt){
	sf::Vector2f pos = shipSprite.getPosition();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pos.x > 0){
		shipSprite.move(sf::Vector2f(-500*dt,0));
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pos.x < 
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
			enemySprite[i].setPosition(pos.x, pos.y + 20);
		}

	}
	
	else if(enemySprite[spriteCols-1].getPosition().x 
		> windowSizeX - enemy.getSize().x){
		dir = LEFT;

		for(int i = 0; i < spriteRows*spriteCols; i++){
			pos = enemySprite[i].getPosition();
			enemySprite[i].setPosition(pos.x, pos.y + 20);
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
	enemyBullet.move(sf::Vector2f(0,200*dt));
}

void Sprites::fireBullet(){
	if(bullet.getPosition().y < 0){
		sf::Vector2f pos = shipSprite.getPosition();
		bullet.setPosition(pos.x+70,pos.y);
		sound.fireSound(); 
	}
}

void Sprites::fireEnemyBullet(float dt){
	int r = rand() % (spriteRows*spriteCols);
	int count = 0;
	while(isDead[r] && count < 15){
		r = rand() % (spriteRows*spriteCols);
		count++;
	}
	if(enemyBullet.getPosition().y > windowSizeY && !isOver){
		sf::Vector2f pos = enemySprite[r].getPosition();
		enemyBullet.setPosition(pos.x,pos.y);
		sound.fireSound(); 
	}
}

void Sprites::detectCollision(){
	sf::FloatRect bulletBounds(bullet.getGlobalBounds());
	for(int i = 0; i < spriteRows* spriteCols; i++){
		if(bulletBounds.intersects(enemySprite[i].getGlobalBounds()) && !isDead[i]){
			isDead[i] = true;
			bullet.setPosition(0,-50);
			sound.explosionSound();
		}

		if((enemySprite[i].getPosition().y >= shipSprite.getPosition().y && !isDead[i])
			|| enemyBullet.getGlobalBounds().intersects(shipSprite.getGlobalBounds())
			|| (enemySprite[i].getGlobalBounds().intersects(shipSprite.getGlobalBounds())
				&& !isDead[i])){
			
			isOver = true;
			isWon = false;
			return;
		}

	}
	for(int i = 0;i<spriteRows*spriteCols; i++){
		if(!isDead[i]){
			return;
		}
	}

	isOver = true;
	isWon = true;
}

void Sprites::drawAll(sf::RenderWindow *window,float dt){
	if(!isOver){

		window->draw(shipSprite);
		window->draw(bullet);
		window->draw(enemyBullet);
		for(int i = 0; i<spriteRows*spriteCols; i++){
			if(!isDead[i]){
				window->draw(enemySprite[i]);
			}
		}

	}else if(isWon){
		//game over scene
		gameOverText.setString("Game Won \nPress Return to restart");
		window->draw(gameOverText);
	}
	else{
		gameOverText.setString("Game Lost \nPress Return to restart");
		window->draw(gameOverText);
	}	

	window->display();
}

int main(){
	sf::RenderWindow window(sf::VideoMode(800,600), "Galaga");
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

				if(event.key.code == sf::Keyboard::Return){
					sprites.reset();
				}
			}

		}
		sprites.moveShip(dt);
		sprites.moveEnemy(dt);
		sprites.fireEnemyBullet(dt);
		sprites.moveBullet(dt);
		sprites.detectCollision();
		sprites.drawAll(&window,dt);

	}
	return 0;
}
