#include "Game.h"
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

Game::Game()
{
}


Game::~Game()
{
}

void Game::run() {
	init(1280, 720);
	gameloop();
}



void Game::init(int width, int height) {
	_width = width;
	_height = height;

	_window.create(sf::VideoMode(width, height), "PhysBox");
	_window.setFramerateLimit(60);
	_window.setVerticalSyncEnabled(true);

	sf::Texture _texture;
	_texture.loadFromFile("Resources/Textures/Wood.jpg");
	_texture.setSmooth(true);
	_textures["wood"] = _texture;

	_texture.loadFromFile("Resources/Textures/bricks.jpg");
	_texture.setSmooth(true);
	_textures["brick"] = _texture;

	_texture.loadFromFile("Resources/Textures/box1.jpg");
	_texture.setSmooth(true);
	_textures["box"] = _texture;

	_texture.loadFromFile("Resources/Textures/box2.jpg");
	_texture.setSmooth(true);
	_textures["box2"] = _texture;


	_texture.loadFromFile("Resources/Textures/box3.jpg");
	_texture.setSmooth(true);
	_textures["box3"] = _texture;

	_texture.loadFromFile("Resources/Textures/circle-blue.png");
	_texture.setSmooth(true);
	_textures["circle-blue"] = _texture;

	_texture.loadFromFile("Resources/Textures/circle-red.png");
	_texture.setSmooth(true);
	_textures["circle-red"] = _texture;

	_texture.loadFromFile("Resources/Textures/circle-green.png");
	_texture.setSmooth(true);
	_textures["circle-green"] = _texture;

	_texture.loadFromFile("Resources/Textures/circle-orange.png");
	_texture.setSmooth(true);
	_textures["circle-orange"] = _texture;

	_texture.loadFromFile("Resources/Textures/sphere-bluewater.png");
	_texture.setSmooth(true);
	_textures["circle-water"] = _texture;

	_texture.loadFromFile("Resources/Textures/circle-white.png");
	_texture.setSmooth(true);
	_textures["circle-white"] = _texture;

	_textures["blank_red"] = _tools.createBlankTexture(256, 256, sf::Color(255, 0, 0,255));
	_textures["blank_green"] = _tools.createBlankTexture(256, 256, sf::Color(0, 255, 0, 255));
	_textures["blank_blue"] = _tools.createBlankTexture(256, 256, sf::Color(0, 0, 255, 255));
	_textures["blank_white"] = _tools.createBlankTexture(256, 256, sf::Color(255, 255, 255, 255));



	_camera.setCenter(_width / 4, _height / 4);
	_camera.setSize(_width / 2, _height / 2);
	_window.setView(_camera);

	_ents.initWorld(b2Vec2(0, 24), 60, 25, true);


	_ents.addRect(0, 250, 295, 500, 15, false, _textures["wood"]);
	_ents.addRect(1, 7, 150, 15, 275, false, _textures["brick"]);
	_ents.addRect(2, 493, 150, 15, 275, false, _textures["brick"]);
	_ents.addRect(3, 250, 7, 500, 15, false, _textures["brick"]);

	_background.createSprite(0, 0, 0, 500, 300,_textures["blank_white"]);
	_background.setColor(0, sf::Color(0, 0, 0, 255));

}
void Game::gameloop() {

	while (_window.isOpen())
	{
		_ents.updateWorld();
		_ents.updateAll();

		input();

		_window.clear(sf::Color(0, 125, 255));
		
		for (auto& x : _background.getSprites()) {
			_window.draw(x.second);
		}

		for (auto& x : _ents.getEntities()) {
			_window.draw(x.second.getSprite());
		}

		for (auto& x : _gui.getSprites()) {
			_window.draw(x.second);
		}
		
		_window.display();

	}
}
void Game::input() {
	sf::Event event;
	if (_window.pollEvent(event)) {
		switch (event.type) {
			
		case sf::Event::Closed:
			_window.close();
			break;

		case sf::Event::MouseButtonPressed:
			_mouse.pressKey(event.mouseButton.button);
			break;
		case sf::Event::MouseButtonReleased:
			_mouse.releaseKey(event.mouseButton.button);
			break;
		case sf::Event::KeyPressed:
			_keyboard.pressKey(event.key.code);
			break;
		case sf::Event::KeyReleased:
			_keyboard.releaseKey(event.key.code);
			break;
		case sf::Event::MouseMoved:
			int x = event.mouseMove.x / 2;
			int y = event.mouseMove.y / 2;

			int w = 3;
			int h = 3;

			if (x >= 485-w/2) {
				x = 485-w/2;
			}
			if (x <= 15+w/2) {
				x = 15 + w / 2;
			}
			if (y >= 287 - h / 2) {
				y = 287 - h / 2;
			}
			if (y <= 15 + h / 2) {
				y = 15 + h / 2;
			}

			_gui.createSprite(0, x-w/2, y-h/2, w, h, _textures["box"]);
			_gui.setColor(0, sf::Color(255, 255, 255, 128));
		}
	}
	
	if(_mouse.getKey(sf::Mouse::Button::Left)){
		_tmp++;
		if (_tmp >= 1) {

			sf::Vector2f pos = _gui.getPosition(0);
			sf::Vector2f size = _gui.getScaleInPixel(0);

			_ents.addRect(_id,pos.x+size.x/2,pos.y+size.y/2,size.x,size.y,true,_textures["circle-water"]);
			_id++;
		}
	}
	else {
		_tmp = 0;
	}

}
