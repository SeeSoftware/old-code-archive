#include <SFML/Graphics.hpp>
#include <GESFML/Tools.h>
#include <GESFML/SpriteBatch.h>
#include <GESFMl/InputManager.h>
#include <iostream>
#include <map>


void main() {

	GESFML::Tools tools;
	GESFML::InputManager IoManager;
	sf::RenderWindow _window;
	sf::Sprite _sprite;
	sf::Texture _texture;
	GESFML::SpriteBatch _batch;
	float zoom=1;
	sf::View view(sf::FloatRect(0, 0, 800, 600));
	sf::Clock Clock;
	int a = 0;
	sf::Vector2f tmp;
	sf::Vector2f tmp_mouse;

	_texture.loadFromFile("54.png");

	_window.create(sf::VideoMode(800, 600), "Game Engine SFML");
	_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(60);



	int id = 0;
	for (int y = 0; y < 128;y += 1) {
		for (int x = 0;x < 128;x +=1) {
			
			_batch.createSprite(id,x*4, y*4, 4, 4, _texture);
			id++;
		}
	}

	

	while (_window.isOpen())
	{

		float Framerate = 1.f / Clock.getElapsedTime().asSeconds();
		Clock.restart();
		//std::cout << Framerate << "\n";

		sf::Event event;
		if (_window.pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed:
				_window.close();
			case sf::Event::MouseWheelMoved:

				if (event.mouseWheel.delta >= 1) {
					zoom = 0.9;
				}
				else if (event.mouseWheel.delta <= -1) {
					zoom = 1.1;
				}
				else {
					zoom = 1;
				}
				view.zoom(zoom);
				_window.setView(view);
				break;

			case sf::Event::MouseButtonPressed:

				IoManager.pressKey(event.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				IoManager.releaseKey(event.mouseButton.button);
				
				break;

			case sf::Event::MouseMoved:
				if (IoManager.getKey(sf::Mouse::Button::Left)) {
					//id--;

					sf::Vector2f tmp = _window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));

					for (int i=0; i < 4;i++) {
						for (int x = 0; x < 4; x++) {
							_batch.createSprite(id, tmp.x + x * 4, tmp.y+i*4, 4, 4, _texture);
							_batch.setColor(id, sf::Color(i * 64, x*64, 0, 255));
							id++;
						}
					}

				}

				
				
				if (IoManager.getKey(sf::Mouse::Button::Right)) {
					//std::cout << "OL";



					a++;
					if (a == 1) {
						tmp = view.getCenter();
						tmp_mouse = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
					}
					std::cout << tmp_mouse.x << " ";
					view.setCenter(-( (sf::Vector2f(event.mouseMove.x - tmp_mouse.x, event.mouseMove.y - tmp_mouse.y))));
					_window.setView(view);

				}
				else {
					a = 0;
				}

				break;
			}

			

		}




		//for (long long unsigned i = 0; i < _batch.getSize();i++) {
		//	_batch.rotatate(i, 1);

		//}

		_window.clear(sf::Color(0, 127, 255));
		
		for (auto& x : _batch.getSprites()) {
			_window.draw(x.second);
		}

		/*
		//************************************************************************************************
		//DRAW ELEMENTS IN ORDER BY ID
		std::map<long long unsigned, sf::Sprite>::key_compare keyComp = _batch.getSpritesKeyCompare();
		std::map<long long unsigned, sf::Sprite> map = _batch.getSprites();

		char highest = map.rbegin()->first;     // key value of last element

		std::map<long long unsigned, sf::Sprite>::iterator it = map.begin();
		do {
			_window.draw(it->second);
	
		}
		while (keyComp((*it++).first, highest));
		
		//************************************************************************************************
		*/
		_window.display();
	}
}

