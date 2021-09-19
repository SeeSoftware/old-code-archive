#pragma once
#include <SFML\Graphics.hpp>
#include <string>

namespace GESFML
{

	class Window
	{
	public:
		Window();
		Window(sf::VideoMode Vmode, std::string title, bool vsync, int maxfps, sf::Uint32 style = sf::Style::Default);
		~Window();

		void create(sf::VideoMode Vmode, std::string title, bool vsync, int maxfps, sf::Uint32 style = sf::Style::Default);
		sf::RenderWindow &getWindow();
		float getFps();
		void updateFps();
		void display();
		void draw(sf::Drawable& drawable, const sf::RenderStates &drawmode = sf::RenderStates::Default);
		bool pollEvent(sf::Event &Event);
		void close();
		bool isOpen();
		void clear(sf::Color color = sf::Color());
		void setViewCenter(sf::Vector2f center);
		void setViewSize(sf::Vector2f size);
		sf::View &getView();

	private:

		sf::RenderWindow _window;
		sf::View _view;
		sf::Clock _fpstimer;
		float _fps;

	};

}
