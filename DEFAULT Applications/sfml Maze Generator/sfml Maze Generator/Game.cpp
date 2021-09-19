#include "Game.h"
#include <iostream>
#include <time.h>
#include <SFML\Graphics.hpp>
#include <GESFML\Window.h>
#include <GESFML\Entity.h>
#include <GESFML\Texture.h>
Game::Game()
{
}


Game::~Game()
{
}


void Game::run() {
	init(800, 800);
	gameLoop();
}


void Game::init(int width, int height) {
	_width = width;
	_height = height;
	_window.init(width, height, "Lol", 60, true);
	


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

	GESFML::Entity entity;
	GESFML::Texture texture;

	//texture.createEmptyTexture(256, 256);
	texture.openPng("54.png");
	entity.setTexture(texture);
	entity.setPosScale(10, 10, 256, 256);

	entity.setColor(sf::Color(255, 0, 0, 255));


	while (_window.isOpen()) {

		

		input();
		_window.clear(sf::Color(0, 128, 255));
		_window.draw(entity);
		_window.update();
	}
	
}


void Game::setPixel(int x, int y, sf::Color color){
	int i = (x + y*_width) * 4;
	
	_pixels[i] = color.r;
	_pixels[i + 1] = color.g;
	_pixels[i + 2] = color.b;
	_pixels[i + 3] = color.a;

}
sf::Color Game::getPixel(int x, int y) {
	int i = (x + y*_width) * 4;
	sf::Color tmp;

	tmp.r=_pixels[i];
	tmp.g=_pixels[i + 1];
	tmp.b=_pixels[i + 2];
	tmp.a=_pixels[i + 3];
	
	return tmp;
}

void Game::runstep() {
	int x = _currentPos.x;
	int y = _currentPos.y;

	int random;

	std::vector<sf::Vector2f> tmpPos;


	if (getPixel(x + 2, y) != sf::Color(255, 255, 255, 255)) {
		tmpPos.push_back(sf::Vector2f(x + 2, y));
	}
	if (getPixel(x - 2, y) != sf::Color(255, 255, 255, 255)) {
		tmpPos.push_back(sf::Vector2f(x - 2, y));
	}
	if (getPixel(x, y+2) != sf::Color(255, 255, 255, 255)) {
		tmpPos.push_back(sf::Vector2f(x, y+2));
	}
	if (getPixel(x, y-2) != sf::Color(255, 255, 255, 255)) {
		tmpPos.push_back(sf::Vector2f(x, y - 2));
	}

	if (tmpPos.empty()) {
		_currentPos = _positions.back();
		_positions.pop_back();
		return;
	}
	
	srand(_randomseed);
	random = rand() % tmpPos.size()-1;

	setPixel(tmpPos[random].x, tmpPos[random].y, sf::Color(255, 255, 255, 255));

	_positions.push_back(tmpPos[random]);
	_currentPos = tmpPos[random];



}