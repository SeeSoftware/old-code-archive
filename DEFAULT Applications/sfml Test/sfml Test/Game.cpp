#include "Game.h"
#include <iostream>
#include "Ball.h"

Game::Game()
{
}


Game::~Game()
{
}


void Game::run() {
	init(800, 600);
	gameLoop();
}


void Game::init(int width, int height) {
	_width = width;
	_height = height;

	_window.create(sf::VideoMode(width, height), "Test SFML");


}

void Game::input() {
	sf::Event Event;
	if (_window.pollEvent(Event)) {
		switch(Event.type) {
		
		case sf::Event::Closed: 
				_window.close();
		default:
			break;
			}

	}

}

void Game::gameLoop() {
	sf::Texture texture;
	sf::Texture texture_ball;
	

	if (!texture.loadFromFile("image.png",sf::IntRect(0,0,256,256))) {
		std::cout << "Error loading texture" << "\n";
	}

	if (!texture_ball.loadFromFile("image_ball.png", sf::IntRect(0, 0, 256, 256))) {
		std::cout << "Error loading texture" << "\n";
	}

	std::vector<Ball> balls;
	balls.push_back(Ball(texture_ball));

	

	int a = 0;
	while (_window.isOpen()) {
		a++;
		if (a % 1000==1) {
			balls.push_back(Ball(texture_ball));
			
		}
		if (a % 1000 == 1) {

			std::cout << balls.size() << " ";
		}

		for (int i = 0;i < balls.size();i++) {
			balls[i].update();
		}
		input();
		
		
		_window.clear(sf::Color(0,128,255));
		for (int i = 0;i < balls.size();i++) {
			balls[i].draw(_window);
		}
		_window.display();
	}
	
} 