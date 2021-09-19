#pragma once
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <GESFML\Tools.h>

#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <unordered_map>
#include <string>
class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void init(int width, int height);
	void gameloop();
	void input();

	void createMusicWindow();
	void MusicPlayerPlaySound();
	void MusicPlayerStopSound();
	void MusicPlayerChangePitch();
	void MusicPlayerCloseWindow();

	int _width, _height;
	int _windowPositonNum;
	

	sf::RenderWindow _sfmlWindow;
	sfg::SFGUI sfGui;
	sfg::Window::Ptr _mainGuiWindow = sfg::Window::Create();
	sfg::Box::Ptr _mainGuiWindowBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL,5);
	sfg::Box::Ptr _mainGuiWindowSubBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL,5);
	sfg::Box::Ptr _mainGuiWindowSubBox2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL,5);
	sfg::Box::Ptr _mainGuiWindowSubBox3 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL,5);
	sfg::Box::Ptr _mainGuiWindowSubBox4 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);

	sfg::Label::Ptr _mainGuiWindowLabel = sfg::Label::Create();
	sfg::Button::Ptr _mainGuiWindowButtonMlg = sfg::Button::Create();
	sfg::Button::Ptr _mainGuiWindowButtonNewWindow = sfg::Button::Create();

	sfg::Desktop _mainDesktop;

	GESFML::Tools _tools;
	sf::Sprite _backGroundSprite;
	sf::Texture _backGroundTexture;
	sf::Sound _mlgSound;
	sf::SoundBuffer _mlgSoundBuffer;
	sf::Sound _musicPlayerSound;
	sf::SoundBuffer _musicPlayerSoundBuffer;

	std::unordered_map<std::string, sfg::Label::Ptr> _sfgLabelPtrContainer;
	std::unordered_map<std::string, sfg::Scale::Ptr> _sfgScalePtrContainer;
};

