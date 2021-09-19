#include "Window.h"

namespace GESFML {

	Window::Window()
	{
	}


	Window::~Window()
	{
	}


	void Window::init(int width, int height, std::string windowtitle, int maxFps, bool Vsync) {
		_width = width;
		_height = height;
		_wintitle = windowtitle;
		_maxFps = maxFps;

		_window.create(sf::VideoMode(width, height), windowtitle);
		_window.setVerticalSyncEnabled(Vsync);
		_window.setFramerateLimit(maxFps);

		_window.display();

	}


	void Window::update() {
		_window.display();

	}

	void Window::close() {
		_window.close();
	}


	void Window::draw(Entity entity) {
		_window.draw(entity.getSprite());

	}
	void Window::clear(sf::Color color) {
		_window.clear(color);

	}

}

