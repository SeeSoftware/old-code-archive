#include "Window.h"

namespace GESFML
{

	Window::Window()
	{
	}

	Window::Window(sf::VideoMode Vmode, std::string title, bool vsync, int maxfps, sf::Uint32 style)
	{
		_window.create(Vmode, title, style);
		_window.setVerticalSyncEnabled(vsync);
		_window.setFramerateLimit(maxfps);

	}

	Window::~Window()
	{
		_window.close();
	}

	void Window::create(sf::VideoMode Vmode, std::string title, bool vsync, int maxfps, sf::Uint32 style)
	{
		_window.create(Vmode, title, style);
		_window.setVerticalSyncEnabled(vsync);
		_window.setFramerateLimit(maxfps);

	}

	sf::RenderWindow &Window::getWindow()
	{
		return _window;
	}

	float Window::getFps()
	{
		return _fps;

	}
	void Window::updateFps()
	{
		_fps = 1.0f / _fpstimer.getElapsedTime().asSeconds();
		_fpstimer.restart();

	}

	void Window::display()
	{
		_window.display();
	}

	void Window::draw(sf::Drawable& drawable, const sf::RenderStates &drawmode)
	{
		_window.draw(drawable, drawmode);
	}

	bool Window::pollEvent(sf::Event &Event)
	{
		return _window.pollEvent(Event);
	}

	void Window::close()
	{
		_window.close();
	}

	bool Window::isOpen()
	{
		return _window.isOpen();
	}

	void Window::clear(sf::Color color)
	{
		_window.clear(color);
	}

	void Window::setViewCenter(sf::Vector2f center)
	{
		_view.setCenter(center);
		_window.setView(_view);
	}

	void Window::setViewSize(sf::Vector2f size)
	{
		_view.setSize(size);
		_window.setView(_view);
	}

	sf::View &Window::getView()
	{
		return _view;
	}

}