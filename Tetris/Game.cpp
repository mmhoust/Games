//
//  Game.cpp
//  Tetris
//
//  Created by Matthew Houston on 7/26/14.
//  Copyright (c) 2014 mmhoust. All rights reserved.
//

#include "Game.h"
const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

Game::Game():mWindow(sf::VideoMode(640,480),"Tetris",sf::Style::Default),grid()
{}

void Game::run() {
    
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
            
			handleInputs();
			update(TimePerFrame);
            
		}
        
		render();
	}
    
}

void Game::render(){
    mWindow.clear(sf::Color::White);
    mWindow.draw(grid);
    mWindow.display();
}

void Game::handleInputs(){
    sf::Event event;
    while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				mWindow.close();
				break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    mWindow.close();
                    break;
                }if (event.key.code == sf::Keyboard::Return){
                    reset();
                    break;
                }
		}
	}
}

void Game::update(sf::Time dt){
   
    grid.update(dt);
}

void Game::reset(){

}