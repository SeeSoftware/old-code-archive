#include "Game.h"



Game::Game()
{
}


Game::~Game()
{
}

void Game::run() {
	init(800, 600);
	gameloop();
}

void Game::init(int width, int height) {
	_window.create(sf::VideoMode(width, height), "Box2D");
	_window.setFramerateLimit(60);
	_window.setVerticalSyncEnabled(true);

	_Box2DBatch.initWorld(b2Vec2(0, 9.8f), 30, 50, true);
	_texture.loadFromFile("stone.png", sf::IntRect(0, 0, 32, 32));



}

void Game::input() {

	sf::Event event;
	if (_window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			_window.close();
			break;
		case sf::Event::MouseButtonPressed:

			_ioManager.pressKey(event.mouseButton.button);
			break;
		case sf::Event::MouseButtonReleased:
			_ioManager.releaseKey(event.mouseButton.button);

			break;

		case sf::Event::MouseMoved:
			if (_ioManager.getKey(sf::Mouse::Button::Left)) {

				_id++;
				_Box2DBatch.addRect(_id, event.mouseMove.x, event.mouseMove.y,50,50, true, _texture);

				}

			
		default:
			break;
		}
	}

}
void Game::gameloop() {
	sf::Texture texture;
	texture.loadFromFile("stone.png", sf::IntRect(0, 0, 32, 32));

	_Box2DBatch.addRect(1000, 350, 500, 550, 50, false, texture);

	while (_window.isOpen()) {
		
		_Box2DBatch.updateAll();
		input();

		_window.clear(sf::Color(0, 128, 255));
	
		for (auto& x : _Box2DBatch.getSpriteBatch().getSprites()) {
			_window.draw(x.second);
		}

		_Box2DBatch.updateWorld();
		_window.display();
	}

}


