#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include <iostream>
#include <string>

namespace GESFML {

	class Window
	{
	public:
		Window();
		~Window();

		void init(int width, int height, std::string windowtitle, int maxFps, bool Vsync);

		bool isOpen() {
			return _window.isOpen();
		}
		bool pollEvent(sf::Event &event) {
			return _window.pollEvent(event);
		}
		void close();

		void update();

		void draw(Entity entity);
		void clear(sf::Color color);


	private:
		sf::RenderWindow _window;
		int _width;
		int _height;
		std::string _wintitle;
		int _maxFps;

	};

}
