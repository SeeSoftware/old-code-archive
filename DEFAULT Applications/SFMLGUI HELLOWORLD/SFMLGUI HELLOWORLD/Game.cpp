#include "Game.h"
#include <random>
#include <sstream>

Game::Game()
{
}


Game::~Game()
{
}

void Game::run()
{
	init(800, 600);
	gameloop();
}



void Game::init(int width, int height)
{
	_width = width;
	_height = height;
	_sfmlWindow.create(sf::VideoMode(width, height), "sfgui Helloworld");
	_sfmlWindow.resetGLStates();
	_sfmlWindow.setVerticalSyncEnabled(true);
	_sfmlWindow.setFramerateLimit(60);

	_mainGuiWindow->SetTitle("Main Window");
	_mainGuiWindow->SetStyle(sfg::Window::Style::BACKGROUND | sfg::Window::Style::TITLEBAR | sfg::Window::Style::SHADOW );
	_mainGuiWindow->SetPosition(sf::Vector2f(_width / 2, _height / 2));
	
	_mlgSoundBuffer.loadFromFile("Resources/Sound/SWAG.wav");
	_mlgSound.setBuffer(_mlgSoundBuffer);

	_musicPlayerSoundBuffer.loadFromFile("Resources/Sound/MusicPlayerMusic.wav");
	_musicPlayerSound.setBuffer(_musicPlayerSoundBuffer);
}
void Game::gameloop()
{
	_backGroundTexture = _tools.createBlankTexture(_width, _height, sf::Color(255, 255, 100, 255));
	_backGroundSprite.setColor(sf::Color(255, 255, 255, 255));
	_backGroundSprite.setPosition(sf::Vector2f(0, 0));
	_backGroundSprite.setTexture(_backGroundTexture);

	_mainGuiWindowLabel->SetText("Main Window");
	_mainGuiWindowButtonMlg->SetLabel("Button1");
	_mainGuiWindowButtonNewWindow->SetLabel("button2");

	_mainGuiWindowButtonMlg->SetId("ButtonMlg");

	_mainGuiWindowSubBox->Pack(_mainGuiWindowLabel);
	_mainGuiWindowSubBox2->Pack(_mainGuiWindowButtonMlg);
	_mainGuiWindowSubBox2->Pack(_mainGuiWindowButtonNewWindow);

	_mainGuiWindowBox->Pack(_mainGuiWindowSubBox);
	_mainGuiWindowBox->Pack(_mainGuiWindowSubBox2);
	_mainGuiWindowBox->Pack(_mainGuiWindowSubBox3);

	_mainGuiWindowBox->SetSpacing(5);

	_mainGuiWindow->Add(_mainGuiWindowBox);

	_mainGuiWindowButtonMlg->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Game::createMusicWindow, this));
	

	_mainDesktop.Add(_mainGuiWindow);
	

	while (_sfmlWindow.isOpen())
	{


		input();
		_mainDesktop.Update(0.f);
		
		_sfmlWindow.clear();

		_sfmlWindow.draw(_backGroundSprite);

		sfGui.Display(_sfmlWindow);
		
		_sfmlWindow.display();
	}

}
void Game::input()
{
	// Process events
	sf::Event event;

	while (_sfmlWindow.pollEvent(event))
	{
		// Every frame we have to send SFML events to the window
		// to enable user interactivity. Without doing this your
		// GUI is nothing but a big colorful picture ;)
		_mainDesktop.HandleEvent(event);

		// Close window : exit
		switch (event.type)
		{
		case sf::Event::Closed:
			_sfmlWindow.close();
			break;

		default:
			break;
		}


	}
}

void Game::createMusicWindow()
{
	_windowPositonNum = _windowPositonNum % 25;

	sfg::Window::Ptr window = sfg::Window::Create();
	window->SetStyle(window->GetStyle() | sfg::Window::Style::CLOSE);
	window->SetTitle("Music Player");
	window->SetPosition(sf::Vector2f(_windowPositonNum * 15 + 15, _windowPositonNum * 15 + 15));

	sfg::Label::Ptr labelTitle = sfg::Label::Create("Music Player");
	sfg::Label::Ptr labelPitch = sfg::Label::Create("Pitch: 100");
	sfg::Button::Ptr buttonPlay = sfg::Button::Create("Play");
	sfg::Button::Ptr buttonStop = sfg::Button::Create("Stop");
	sfg::Scale::Ptr pitchScale = sfg::Scale::Create(sfg::Scale::Orientation::HORIZONTAL);

	_mainDesktop.SetProperty("Label#labelTitle", "FontSize", 20);

	labelTitle->SetId("labelTitle");

	pitchScale->GetAdjustment()->SetLower(0.01f);
	pitchScale->GetAdjustment()->SetUpper(2.55f);
	pitchScale->GetAdjustment()->SetMinorStep(0.01f);
	pitchScale->GetAdjustment()->SetValue(1);

	pitchScale->SetRequisition(sf::Vector2f(80, 25));

	buttonPlay->SetRequisition(sf::Vector2f(75, 30));
	buttonStop->SetRequisition(sf::Vector2f(75, 30));

	_sfgLabelPtrContainer["MusicPlayerPitch"] = labelPitch;
	_sfgScalePtrContainer["MusicPlayerPitch"] = pitchScale;

	sfg::Box::Ptr mainBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL,10);
	sfg::Box::Ptr subBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10);
	sfg::Box::Ptr subBox2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10);
	

	subBox->Pack(pitchScale);
	subBox->Pack(labelPitch,true,false);
	subBox2->Pack(buttonPlay);
	subBox2->Pack(buttonStop);
	

	mainBox->Pack(labelTitle);
	mainBox->Pack(subBox);
	mainBox->Pack(subBox2);

	
	buttonStop->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Game::MusicPlayerStopSound, this));
	buttonPlay->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Game::MusicPlayerPlaySound, this));
	window->GetSignal(sfg::Window::OnCloseButton).Connect(std::bind(&Game::MusicPlayerCloseWindow, this));
	pitchScale->GetSignal(sfg::Scale::OnMouseMove).Connect(std::bind(&Game::MusicPlayerChangePitch, this));


	window->Add(mainBox);
	_mainDesktop.Add(window);

	_windowPositonNum++;
	
}

void Game::MusicPlayerPlaySound()
{
	_musicPlayerSound.play();
	_musicPlayerSound.setLoop(true);
	
}

void Game::MusicPlayerStopSound()
{
	_musicPlayerSound.stop();
}

void Game::MusicPlayerCloseWindow()
{
	_musicPlayerSound.stop();
	_sfgScalePtrContainer.erase("MusicPlayerPitch"); //Properly Remove pointers
	_sfgLabelPtrContainer.erase("MusicPlayerPitch"); //Properly Remove Pointers

	// Obtain parent window.
	auto widget = sfg::Context::Get().GetActiveWidget();

	while (widget->GetName() != "Window")
	{
		widget = widget->GetParent();
	}

	// Remove window from desktop.
	_mainDesktop.Remove(widget);
}

void Game::MusicPlayerChangePitch()
{
	std::stringstream ss;
	sfg::Label::Ptr pitchLabel = _sfgLabelPtrContainer["MusicPlayerPitch"];
	sfg::Scale::Ptr pitchScale = _sfgScalePtrContainer["MusicPlayerPitch"];
	_musicPlayerSound.setPitch(pitchScale->GetAdjustment()->GetValue());
	ss << "Pitch: " << round(pitchScale->GetAdjustment()->GetValue() * 100);
	pitchLabel->SetText(ss.str().c_str());
}

/*
// Custom properties.
sfg::Context::Get().GetEngine().SetProperties(
	"Button#guess {"   //normal stle  type#id
	"	BackgroundColor: #006400FF;"
	"	BorderColor: #006400FF;"
	"}"
	"Button#guess:Prelight {"     //if you hover over the button
	"	BackgroundColor: #008200FF;"
	"	BorderColor: #008200FF;"
	"}"
	);
	*/