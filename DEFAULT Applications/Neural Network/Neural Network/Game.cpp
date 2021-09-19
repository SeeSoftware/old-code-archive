#include "Game.h"
#include <iostream>



Game::Game()
{
}


Game::~Game()
{
}

void Game::run() {
	init(800, 600, 500, 400);
	mainloop();
}

void Game::init(int MainWidth, int MainHeight, int SecondWidth, int SecondHeight) {
	_mainHeight = MainHeight;
	_mainWidht = MainWidth;
	_secondWidth = SecondWidth;
	_secondHeight = SecondHeight;

	_mainWindow.create(sf::VideoMode(MainWidth, MainHeight), "Neural Network",sf::Style::Close);
	_secondWindow.create(sf::VideoMode(SecondWidth, SecondHeight), "Info", sf::Style::Close);

	_mainCamera.setSize(sf::Vector2f(MainWidth, MainHeight));
	_mainCamera.setCenter(sf::Vector2f(MainWidth/2, MainHeight/2));

	_mainWindow.setView(_mainCamera);

	sf::Texture _tmp;
	_tmp.loadFromFile("Resources/Textures/Grid.png");
	_textures["Grid"]=_tmp;
	_tmp.loadFromFile("Resources/Textures/grass.png");
	_textures["Grass"] = _tmp;
	_tmp.loadFromFile("Resources/Textures/Stone1.png");
	_textures["Stone1"] = _tmp;
	_tmp.loadFromFile("Resources/Textures/Stone2.png");
	_textures["Stone2"] = _tmp;

	_world.init(0, 0, 100, 100, _textures);

}

void Game::input_main() {
	sf::Event event;
	if (_mainWindow.pollEvent(event)) {
		
		switch (event.type) {
		
		case sf::Event::Closed:
			_mainWindow.close();
			break;

		default:
			break;
		}
	}
}

void Game::input_second() {
	sf::Event event;
	if (_secondWindow.pollEvent(event)) {

		switch (event.type) {

		case sf::Event::Closed:
			_secondWindow.close();
			break;
			
		default:
			break;
		}
	}
}

void Game::mainloop() {

	sf::Clock clock;
	float Time;
	float framerate;


	while (_mainWindow.isOpen()&&_secondWindow.isOpen()) {

		Time = clock.getElapsedTime().asSeconds();
		framerate = 1.f / Time;
		clock.restart();

		std::cout << framerate << "\n";

		input_main();
		input_second();

		_mainWindow.clear();
		_secondWindow.clear();

		for (auto x : _world.getSpriteBatch().getSprites()) {
			_mainWindow.draw(x.second);
		}

		_mainWindow.display();
		_secondWindow.display();

		

	}
	_mainWindow.close();
	_secondWindow.close();

}
